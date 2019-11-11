#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 2006, SV = 306;
const double INF = 1e17 + 6;
int N, M, V, E, C[SN], D[SN], sp[SV][SV];
double K[SN], f[SN][SN][2];

int main() {
  ms(sp, 0x3f);
  scanf("%d%d%d%d", &N, &M, &V, &E);
  f(i, 1, N) scanf("%d", &C[i]);
  f(i, 1, N) scanf("%d", &D[i]);
  f(i, 1, N) scanf("%lf", &K[i]);
  f(i, 1, E) {
    reg a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    sp[a][b] = sp[b][a] = min(sp[a][b], w);
  }
  f(k, 1, V) f(i, 1, V) f(j, 1, V) sp[i][j] =
      min(sp[i][j], sp[i][k] + sp[k][j]);
  f(i, 1, V) sp[i][0] = sp[0][i] = sp[i][i] = 0;
  f(i, 0, N) f(j, 0, M) f[i][j][0] = f[i][j][1] = INF;
  f[1][0][0] = f[1][1][1] = 0;
  f(i, 2, N) {
    f[i][0][0] = f[i - 1][0][0] + sp[C[i - 1]][C[i]];
    f(j, 1, min(i, M)) {
      f[i][j][0] =
          min(f[i][j][0], min(f[i - 1][j][0] + sp[C[i - 1]][C[i]],
                              f[i - 1][j][1] + sp[D[i - 1]][C[i]] * K[i - 1] +
                                  sp[C[i - 1]][C[i]] * (1 - K[i - 1])));
      f[i][j][1] =
          min(f[i][j][1],
              min(f[i - 1][j - 1][0] + sp[C[i - 1]][D[i]] * K[i] +
                      sp[C[i - 1]][C[i]] * (1 - K[i]),
                  f[i - 1][j - 1][1] + sp[D[i - 1]][D[i]] * K[i - 1] * K[i] +
                      sp[C[i - 1]][D[i]] * (1 - K[i - 1]) * K[i] +
                      sp[D[i - 1]][C[i]] * K[i - 1] * (1 - K[i]) +
                      sp[C[i - 1]][C[i]] * (1 - K[i - 1]) * (1 - K[i])));
    }
  }
  register double ans = INF;
  f(j, 0, M) ans = min(ans, min(f[N][j][0], f[N][j][1]));
  printf("%.2lf\n", ans);
}
