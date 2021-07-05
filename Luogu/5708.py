import math

a, b, c = input().split()
a = float (a)
b = float (b)
c = float (c)
p = (a + b + c)/2.0
print("%.1f" % math.sqrt(p*(p-a)*(p-b)*(p-c)))