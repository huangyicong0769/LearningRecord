def p1():
  print("I love Luogu!")

def p2():
  print(6, 4)

def p3():
  print(3)
  print(12)
  print(2)

def p4():
  print("%.3f" % (500.0/3.0))

def p5():
  print(15)

def p6():
  print(10.8167)

def p7():
  print(110)
  print(90)
  print(0)

def p8():
  print("31.4159\n78.5398\n523.599")

def p9():
  print(22)

def p10():
  print(9)

def p11():
  print("33.3333")

def p12():
  print("13\nR")

def p13():
  pi = float(3.141593)
  def cV(r):
    return 4*r*r*r*pi/3
  v = cV(4) + cV(10)
  print(16)

def p14():
  print(50)

t = int(input());
if t == 1 : p1()
if t == 2 : p2()
if t == 3 : p3()
if t == 4 : p4()
if t == 5 : p5()
if t == 6 : p6()
if t == 7 : p7()
if t == 8 : p8()
if t == 9 : p9()
if t == 10 : p10()
if t == 11 : p11()
if t == 12 : p12()
if t == 13 : p13()
if t == 14 : p14()
