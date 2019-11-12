#include <cstdio>
#include <cstring>
#define reg register int
#define f(i, s, t) for (reg i = s; i < t; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

typedef long long ll;
const int ST = 80;
int N, T;
ll M, P;

struct Matrix {
  ll n, m, a[ST][ST];
  Matrix operator*(Matrix b) {
    Matrix c = {n, b.m, {0}};
    ms(c.a, 0);
    f(i, 0, n) f(j, 0, b.m)
        f(k, 0, m)(c.a[i][j] += (a[i][k] * b.a[k][j]) % P) %= P;
    return c;
  }
} a, b;

il ll read() {
  register ll x = 0;
  register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

Matrix power(Matrix a, ll n) {
  Matrix b = {a.n, a.m, {0}};
  ms(b.a, 0);
  f(i, 0, b.n) b.a[i][i] = 1;
  for (; n; n >>= 1) {
    if (n & 1) b = b * a;
    a = a * a;
  }
  return b;
}

int main() {
  N = read();
  f(i, 0, N) a.a[0][read()]++;
  T = read(), M = read(), P = read();
  a.n = 1, a.m = T;
  b.n = b.m = T;
  f(i, 0, T) {
    if (i + 1 >= 2 && i + 1 != T) b.a[i][0] = 1;
    if (i + 1 < T) b.a[i][i + 1] = 1;
  }
  a = a * power(b, M - 1);
  register ll ans = 0;
  f(i, 0, T)(ans += a.a[0][i]) %= P;
  printf("%lld\n", ans);
}