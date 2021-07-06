import math

x, n = input().split()
x = int (x)
n = int (n)

t = math.floor(n/7)
n %= 7

ans = t*5*250
l = [0, 1, 1, 1, 1, 1, 0, 0]
while n:
  n -= 1
  ans += l[x]*250
  x += 1
  if x > 7 : x = 1

print(ans)