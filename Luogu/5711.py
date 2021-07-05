y = int(input())

ans = 1 if y % 4 == 0 else 0
if y % 100 == 0 and y % 400 != 0 : ans = 0

print(ans)