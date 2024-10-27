import json
import requests
import asyncio
import aiohttp
import sys
import random

db_ep = ""
gcache_ep = []

with open(sys.argv[1], 'r', encoding='utf8') as f:
    cfg = json.load(f)
    db_ep = cfg['db_url']
    gcache_ep = cfg['cache_urls']

cached = {}

async def put_val(ep, key, val):
    global fail_detected
    async with aiohttp.ClientSession() as session:
        key_url = ep + key
        while True:
            try:
                async with session.put(key_url, data=val, timeout=0.1) as r:
                    if r.status == 400:
                        print('Incorrect PUT request', file=sys.stderr)
                        return True, ep
                    if r.status == 200:
                        return True, ep
                    if r.status == 502:
                        fail_detected = True
                        print("502Error on PUT", file=sys.stderr)
                        return False, ep
            except TimeoutError:
                print("TimeoutError", file=sys.stderr)
                return False, ep
    
    
async def put_cache(cache_ep, key, val, gen, no_fail):
    tasks = []
    if no_fail:
        tasks.append(asyncio.create_task(put_val(cache_ep[gen % len(cache_ep)], key, val)))
    else:
        tasks.append(asyncio.create_task(put_val(cache_ep[gen % len(cache_ep)], key, val)))
        tasks.append(asyncio.create_task(put_val(cache_ep[(gen + 1) % len(cache_ep)], key, val)))
        
    done, pending = await asyncio.wait(tasks)
    for x in done:
        ok, ep = x.result()
        if not ok:
            print(ep, file=sys.stderr)
            return True, ep
    return (False or no_fail), None

async def get_val(session, ep, key):
    key_url = ep + key
    while True:
        try:
            async with session.get(key_url, timeout=0.1) as r:
                if r.status == 404:
                    return None, None
                if r.status == 400:
                    print('Incorrect GET request', file=sys.stderr)
                    return None, None
                if r.status == 200:
                    return await r.text(), None
                if r.status == 502:
                    fail_detected = True
                    print("502Error on GET", file=sys.stderr)
                    return None, ep
        except TimeoutError:
            print("TimeoutError", file=sys.stderr)
            return None, ep

async def check_cache(cache_ep, sessions, key, no_fail):
    tasks = []
    for ep, session in zip(cache_ep, sessions):
        tasks.append(asyncio.create_task(get_val(session, ep, key)))
    finished, tasks = await asyncio.wait(tasks)
    res = None
    failed = None
    for x in finished:
        val, ep = x.result()
        if not (val is None):
            if no_fail:
                return val, None
            res = val
        if not (ep is None):
            failed = ep
    return res, failed

async def main(cache_ep):
    try:
        cached = {}
        gen = random.randint(0, len(cache_ep) - 1)
        fail_detected = False
        sessions = []
        for x in cache_ep:
            sessions.append(aiohttp.ClientSession())
        db_session = aiohttp.ClientSession()
        while True:
            s = sys.stdin.readline()
            if s == "":
                return
            if s in cached:
                print(cached[s])
                sys.stdout.flush()
                sys.stderr.flush()
                continue
            val, failed_on = await check_cache(cache_ep, sessions, s, fail_detected)
            if not (failed_on is None):
                cache_ep.remove(failed_on)
                fail_detected = True
            if val is None:
                #print('Req in DB', file=sys.stderr)
                val, _ = await get_val(db_session, db_ep, s)
                if val is None:
                    print('No key in DB', file=sys.stderr)
                    continue
                old_failure = fail_detected
                fail_detected, ep = await put_cache(cache_ep, s, val, gen, fail_detected)
                if old_failure:
                    gen = (gen + 1) % len(cache_ep)
                else:
                    gen = (gen + 2) % len(cache_ep)
                if old_failure != fail_detected:
                    print(ep, file=sys.stderr)
                    cache_ep.remove(ep)
                    fail_detected = True
                cached[s] = val
                print(val)
            else:
                cached[s] = val
                #print('From cache', file=sys.stderr)
                print(val)
            sys.stdout.flush()
            sys.stderr.flush()
    except EOFError as e:
        return

random.seed(78563)
asyncio.run(main(gcache_ep))