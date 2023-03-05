from subprocess import PIPE, Popen
import random
import sys

n = 10000

def check(a, b, p):
    proc = Popen(['bin\\Debug\\F.exe'], stdin=PIPE, stdout=PIPE, stderr=sys.stdout, bufsize=1, universal_newlines=True)
    print(n, file=proc.stdin)
    proc.stdin.flush()
    done = 0
    steps = 0
    spent_time = 0
    expected_time = n * (a + b) / 2.0 + (n / (1.0 - p) - n) * b

    print("Expected time = " + str(expected_time))

    replies = []

    while True:
        steps += 1
        out = proc.stdout.readline()
        t = int(out)
        replies.append(t)
        f = random.random()
        if f <= p:
            spent_time += t
            print(-1, file=proc.stdin)
            proc.stdin.flush()
            continue
        x = random.randint(a, b)
        if x > t:
            spent_time += t
            print(-1, file=proc.stdin)
            proc.stdin.flush()
        else:
            done += 1
            if done == n:
                break
            spent_time += x
            print(x, file=proc.stdin)
            proc.stdin.flush()

    print("Spent time = " + str(spent_time))
    rel = float(spent_time) / expected_time
    print("Related = " + str(rel))
    if rel > 1.1:
        print("a = " + str(a))
        print("b = " + str(b))
        print("p = " + str(p))
        print("steps = " + str(steps))
        print(replies[0:1000])
        proc.kill()
        sys.exit(1)
    proc.kill()
 

#check(1, 1, 0.01)
 
for a in range(1, 1001):
    for b in range(a, 1001):
        p = 0.0
        while p <= 0.5:
            check(a, b, p)
            p += 0.01
