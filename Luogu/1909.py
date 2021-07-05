import math

n = float(input())
l = []
for i in range(0, 3):
  a, b = input().split()
  a = float(a)
  b = int(b)
  m = math.ceil(n/a)
  l.append(m*b)
l.sort()

print(l[0])