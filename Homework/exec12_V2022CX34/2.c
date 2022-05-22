#include <stdio.h>

struct Complex{
  int rl, ig;
};

typedef struct Complex Complex;

int read() {
  register int x = 0, sign = 1;
  register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') sign = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x*sign;
}

Complex input(){
  return (Complex){read(), read()};
}

void output(const Complex cp){
  if (cp.ig >= 0) printf("%d+%di\n", cp.rl, cp.ig);
  else printf("%d%di\n", cp.rl, cp.ig);
}

Complex mul(const Complex a, const Complex b){
  return (Complex){a.rl*b.rl - a.ig*b.ig, a.rl*b.ig + a.ig*b.rl};
}

int main(){
  output(mul(input(), input()));
}