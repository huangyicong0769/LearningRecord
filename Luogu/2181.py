n = int (input())

if n <= 3 : ans = 0
else: ans = n*(n-1)*(n-2)*(n-3)//24

print(int(ans))