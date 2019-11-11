#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)

const int SN = 1006, SM = 206, P = 1000000007;
char sa[SN], sb[SM];
int N, M, K;
long long f[2][SM][SM][2];

int main() {
  scanf("%d%d%d%s%s", &N, &M, &K, sa + 1, sb + 1);
  f[0][0][0][0] = f[1][0][0][0] = 1;
  f(i, 1, N) f(j, 1, M) f(k, 1, M) {
    f[i % 2][j][k][0] = (f[(i - 1) % 2][j][k][0] + f[(i - 1) % 2][j][k][1]) % P;
    f[i % 2][j][k][1] = sa[i] == sb[j] ? (f[(i - 1) % 2][j - 1][k][1] +
                                          f[(i - 1) % 2][j - 1][k - 1][1] +
                                          f[(i - 1) % 2][j - 1][k - 1][0]) %
                                             P
                                       : 0;
  }
  printf("%lld\n", (f[N % 2][M][K][0] + f[N % 2][M][K][1]) % P);
}