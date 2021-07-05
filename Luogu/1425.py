a, b, c, d = input().split();
a = int(a)
b = int(b)
c = int(c)
d = int(d)
e = c - a
f = d - b
while f < 0:
  f += 60
  e -= 1
print(e, f)