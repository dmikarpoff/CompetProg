import string
import copy

def gcd(x, y):
	while y != 0:
		(x, y) = (y, x % y)
	return x

t = int(input())
for o in range(0, t):
	temp = input().split(' ')
	n = int(temp[0])
	l = int(temp[1])
	cipher = [int(x) for x in input().split(' ')]
	pos = 0
	for i in range(len(cipher) - 1):
		if cipher[i] != cipher[i + 1]:
			pos = i
			break;
	c = gcd(cipher[pos], cipher[pos +  1])
	cipher.insert(pos + 1, c)
	for i in range(pos, -1, -1):
		cipher[i] = cipher[i] // cipher[i + 1]
	for i in range(pos + 2, len(cipher)):
		cipher[i] = cipher[i] // cipher[i - 1] 
	codes = sorted(set(cipher))
	res = ""
	for c in cipher:
		res += string.ascii_uppercase[codes.index(c)]
	print('Case #{}: {}'.format(o + 1, res))