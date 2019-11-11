#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 19;
const double eps = 1e-6;
int T, N, M, line[SN][SN], g[1 << SN], f[1 << SN];
double x[SN], y[SN];

int main() {
  f(i, 0, (1 << SN) - 1) {
    reg int j = 1;
    while (j < SN && i & (1 << (j - 1))) j++;
    g[i] = j;
  }
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);
    ms(line, 0), ms(f, 0x3f);
    f(i, 1, N) scanf("%lf%lf", &x[i], &y[i]);
    f(i, 1, N) f(j, 1, N) {
      if (fabs(x[i] - x[j]) <= eps) continue;
      reg double a = (x[i] * y[j] - x[j] * y[i]) / (x[i] * x[j] * x[j] - x[i] * x[i] * x[j]),
                 b = (x[i] * x[i] * y[j] - x[j] * x[j] * y[i]) / (x[i] * x[i] * x[j] - x[i] * x[j] * x[j]);
      if (a > -eps) continue;
      // printf("%d %d %.2lf %.2lf\n", i, j, a, b);
      f(k, 1, N) if (fabs(y[k] - a * x[k] * x[k] - b * x[k]) <= eps) line[i][j] |= 1 << (k - 1);
    }
    f[0] = 0;
    f(i, 0, (1 << N) - 1) {
      reg int j = g[i];
      f[i | (1 << (j - 1))] = min(f[i | (1 << (j - 1))], f[i] + 1);
      f(k, 1, N) f[i | line[j][k]] = min(f[i | line[j][k]], f[i] + 1);
    }
    printf("%d\n", f[(1 << N) - 1]);
  }
}
