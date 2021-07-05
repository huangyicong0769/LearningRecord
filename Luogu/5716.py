y, m = input().split()
y = int (y)
m = int (m)

ly = True if y % 4 == 0 else False
if y % 100 == 0 and y % 400 != 0 : ly = False

md = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

if ly and m == 2 : print(29)
else : print(md[m])