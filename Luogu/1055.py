s = input()
q = 0
i = 0
for c in s:
  if c == '-': continue
  i += 1
  if i > 9 : break
  q += i*int(c)
q %= 11
if q == 10 : q = 'X'
else: q = str(q)
if q == s[12] : print("Right")
else: print(s[:12]+q)