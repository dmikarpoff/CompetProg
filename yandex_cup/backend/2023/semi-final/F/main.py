import sys
import json
import requests
import asyncio
import aiohttp

cfg_file = sys.argv[1]
with open(cfg_file, 'r', encoding="utf8") as f:
    cfg_data = json.load(f)

server_ep = cfg_data["server"]["endpoint"]
#print(server_ep)

sensors = {}

for x in cfg_data["sensors"]:
    sensors[x["endpoint"]] = x["name"]

async def scan_sensor(sensor):
    async with aiohttp.ClientSession() as session:
        sensor_url = "http://" + sensor + "/state"
        #print(sensor_url)
        sens = True
        while sens:
            try:
                async with session.get(sensor_url, timeout=1) as r:
                    #print("Response " + str(r.status));
                    print(r.headers)
                    if r.ok:
                        data = await r.text()
                        data = json.loads(data)
                        dmid = data["dmid"]
                        state = data["state"]
                        sens = False
                    else:
                        return
            except asyncio.TimeoutError as e:
                return
        print("Data extracted")
    
        posted = False
        server_url = "http://" + server_ep + "/send_measurings"
        while not posted:
            try:
                async with session.post(server_url, json={"meter_device_id": dmid, 'measurings': state}, timeout=1) as r:
                    #print("!!!Server");
                    print(r.headers)
                    if r.ok:
                        #print("Done")
                        posted = True
                    else:
                        await asyncio.sleep(0.1)
            except asyncio.TimeoutError as e:
                await asyncio.sleep(0.1)

        
async def run():
    tasks = []
    for ep, name in sensors.items():
        task = asyncio.create_task(scan_sensor(ep))
        tasks.append(task)
    await asyncio.gather(*tasks)

asyncio.run(run())
