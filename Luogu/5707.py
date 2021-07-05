import math

s, v = input().split()
s = int (s)
v = int (v)

m = math.ceil(s/v) + 10
h = math.floor(m/60)
m -= h*60
h += 1
h = 8 - h
if h < 0 : h += 24
m = 60 - m

while m >= 60 : 
  m -= 60
  h += 1
  if h >= 24 : h -= 24
if h < 10 : print("0%d" % h, end = ":")
else: print("%d" % h, end = ":")
if m < 10 : print("0%d" % m)
else: print("%d" % m)