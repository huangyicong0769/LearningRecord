n = int (input())

q1 = not bool(n%2)
if n >= 4 and n <= 12 : q2 = True
else: q2 = False

#print(q1, q2)
print(int(q1&q2), int(q1|q2), int(q1^q2), int(q1 == 0 and q2 == 0))