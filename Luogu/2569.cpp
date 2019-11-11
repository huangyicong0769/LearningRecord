#include <cstdio>
#include <cstring>
#include <iostream>
#define SIZE 2006
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

int T, W, P, f[SIZE][SIZE], q[SIZE];

int main() {
  memset(f, 0xcf, sizeof(f));
  scanf("%d%d%d", &T, &P, &W);
  f(i, 1, T) {
    reg ap, bp, as, bs;
    scanf("%d%d%d%d", &ap, &bp, &as, &bs);
    f(j, 0, as) f[i][j] = max(f[i][j], -ap * j);
    f(j, 0, P) f[i][j] = max(f[i][j], f[i - 1][j]);
    if (i - W - 1 < 0) continue;
    reg l = 1, r = 0;
    f(j, 0, P) {
      while (l <= r && q[l] + as < j) l++;
      if (l <= r)
        f[i][j] = max(f[i][j], f[i - W - 1][q[l]] + q[l] * ap - j * ap);
      while (l <= r &&
             f[i - W - 1][q[r]] + q[r] * ap - j * ap <= f[i - W - 1][j])
        r--;  
      q[++r] = j;
    }
    l = 1, r = 0;
    for (reg j = P; j >= 0; j--) {
      while (l <= r && j + bs < q[l]) l++;
      if (l <= r)
        f[i][j] = max(f[i][j], f[i - W - 1][q[l]] + q[l] * bp - j * bp);
      while (l <= r &&
             f[i - W - 1][q[r]] + q[r] * bp - j * bp <= f[i - W - 1][j])
        r--;
      q[++r] = j;
    }
  }
  // reg ans = -(1 << 30);
  // f(i, 0, P) ans = max(ans, f[T][i]);
  printf("%d\n", f[T][0]);
}