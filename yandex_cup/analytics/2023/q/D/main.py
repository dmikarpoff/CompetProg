n = int(input())
a = [int(x) for x in input().split(sep=' ')]

cnt = [0] * 100001
for x in a:
  cnt[x] += 1
  
t = n
i = 0
for x in cnt:
  cnt[i] = t
  i += 1
  t -= x

k = 0
while cnt[k * k] >= k:
  k += 1

print(k - 1)
#print(cnt[0:10])