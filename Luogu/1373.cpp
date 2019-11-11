#include <iostream>
#include <cstdio>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 806, SK = 18, P = 1000000007;
int f[SN][SN][SK][2], a[SN][SN], N, M, K;

il int read(){
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar());
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

int main() {
  N = read(), M = read(), K = read() + 1;
  f(i, 1, N) f(j, 1, M) f[i][j][a[i][j] = read() % K][0] = 1;
  f(i, 1, N) f(j, 1, M) f(k, 0, K) {
    (f[i][j][k][0] += f[i - 1][j][(k - a[i][j] + K) % K][1]) %= P;
    (f[i][j][k][0] += f[i][j - 1][(k - a[i][j] + K) % K][1]) %= P;
    (f[i][j][k][1] += f[i - 1][j][(k + a[i][j] + K) % K][0]) %= P;
    (f[i][j][k][1] += f[i][j - 1][(k + a[i][j] + K) % K][0]) %= P;
  }
  long long ans = 0;
  f(i, 1, N) f(j, 1, M) (ans += f[i][j][0][1]) %= P;
  printf("%lld\n", ans);
}