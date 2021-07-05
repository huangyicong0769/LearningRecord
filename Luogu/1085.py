ans = 0
for i in range(1, 7):
  a, b = input().split()
  a = int (a)
  b = int (b)
  if (a + b) > 8 : 
    ans = i
    break

print(ans)