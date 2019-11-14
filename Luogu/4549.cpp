#include <cstdio>
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)

inline int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main() {
  reg N = read() - 1, ans = read();
  while (N--) ans = gcd(ans, read());
  printf("%d\n", ans);
}