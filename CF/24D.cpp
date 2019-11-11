#include <cstdio>
#include <iostream>
#define SIZE 1006
#define reg register
#define rg reg int
#define f1(i, s, t) for (rg i = s; i != t; i++)
#define f2(i, s, t) for (rg i = s; i != t; i--)
using namespace std;

double f[SIZE], a[SIZE][SIZE];

int main() {
  int N, M, X, Y;
  scanf("%d%d%d%d", &N, &M, &X, &Y);
  f2(i, N - 1, X - 1) {
    if (M == 1) {
      a[1][1] = -1.0 / 2.0;
      a[1][M + 1] = -f[1] / 2.0 - 1;
    } else {
      a[1][1] = a[M][M] = -2.0 / 3.0;
      a[1][2] = a[M][M - 1] = 1.0 / 3.0;
      a[1][M + 1] = -f[1] / 3.0 - 1;
      a[M][M + 1] = -f[M] / 3.0 - 1;
      f1(j, 2, M) {
        a[j][j + 1] = a[j][j - 1] = 1.0 / 4.0;
        a[j][j] = -3.0 / 4.0;
        a[j][M + 1] = -f[j] / 4.0 - 1;
      }
    }
    f1(j, 1, M) {
      double r = a[j + 1][j] / a[j][j];
      a[j + 1][j] -= a[j][j] * r;
      a[j + 1][j + 1] -= a[j][j + 1] * r;
      a[j + 1][M + 1] -= a[j][M + 1] * r;
    }
    f[M] = a[M][M + 1] / a[M][M];
    f2(j, M - 1, 0) f[j] = (a[j][M + 1] - f[j + 1] * a[j][j + 1]) / a[j][j];
  }
  printf("%.10lf\n", f[Y]);
}
