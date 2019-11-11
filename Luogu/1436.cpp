#include <cstdio>
#include <iostream>
#define reg register
#define f(i, s, t) for (reg int i = s; i != t; i++)
using namespace std;

const int M = 9;
int f[M][M][M][M][16], s[M][M], N;

int main() {
  scanf("%d", &N);
  f(i, 1, M) f(j, 1, M) scanf("%d", &s[i][j]),
      s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
  f(x1, 1, M) f(y1, 1, M) f(x2, x1, M) f(y2, y1, M)
      f[x1][y1][x2][y2][0] =
          s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1],
      f[x1][y1][x2][y2][0] *= f[x1][y1][x2][y2][0];
  // f(x1, 1, M) f(y1, 1, M) f(x2, x1, M) f(y2, y1, M)
  // printf("f[%d][%d][%d][%d][0]=%d\n", x1, y1, x2, y2, f[x1][y1][x2][y2][0]);
  f(k, 1, N) f(x1, 1, M) f(y1, 1, M) f(x2, x1, M) f(y2, y1, M) {
    f[x1][y1][x2][y2][k] = 0x3f3f3f3f;
    f(i, x1, x2) f[x1][y1][x2][y2][k] =
        min(min(f[i + 1][y1][x2][y2][0] + f[x1][y1][i][y2][k - 1],
                f[i + 1][y1][x2][y2][k - 1] + f[x1][y1][i][y2][0]),
            f[x1][y1][x2][y2][k]);
    f(j, y1, y2) f[x1][y1][x2][y2][k] =
        min(min(f[x1][j + 1][x2][y2][0] + f[x1][y1][x2][j][k - 1],
                f[x1][j + 1][x2][y2][k - 1] + f[x1][y1][x2][j][0]),
            f[x1][y1][x2][y2][k]);
  }
  printf("%d\n", f[1][1][8][8][N - 1]);
}