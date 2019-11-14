#include <cstdio>
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)

inline int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

int main() {
  reg a = read(), m = read();
  reg tmp = m, phi = m;
  for (reg i = 2; i * i <= m; i++)
    if (tmp % i == 0) {
      phi -= phi / i;
      while (tmp % i == 0) tmp /= i;
    }
  if (tmp > 1) phi -= phi / tmp;
  reg b = 0, f = 0;
  register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) {
    b = b * 10 + ch - '0';
    if (b >= phi) f = 1, b %= phi;
  }
  if (f) b += phi;
  reg ans = 1;
  for (; b; b >>= 1){
    if (b & 1) ans = 1LL * ans * a % m;
    a = 1LL * a * a % m;
  }
  printf("%d\n", ans);
}