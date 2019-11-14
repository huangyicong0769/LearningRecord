#include <cstdio>
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)

inline int read(){
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

int main(){
  reg T = read();
  while (T--){
    reg N = read(), ans = 0;
    while (N--) ans ^= read();
    ans ? puts("Yes") : puts("No");
  }
}