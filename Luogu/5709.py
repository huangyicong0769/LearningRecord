import math

m, t, s = input().split()
m = int (m)
t = float (t)
s = float (s)

ans = 0
if t != 0 :
  n = math.ceil (s / t)
  ans = m - n
if t == 0 or ans < 0:
  ans = 0

print(ans)