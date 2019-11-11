#include <cstdio>
#include <cstring>
#include <iostream>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a));
using namespace std;

const int SIZE = 1006, P = (1 << 31) - 1;
int N, M, a[SIZE][SIZE], d[SIZE];
bool b[SIZE];

int main() {
  scanf("%d%d", &N, &M);
  ms(a, 0x3f);
  f(i, 1, N) a[i][i] = 0;
  f(i, 1, M) {
    reg x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    a[x][y] = a[y][x] = min(a[x][y], z);
  }
  ms(d, 0x3f);
  ms(b, 0);
  d[1] = 0;
  f(i, 2, N) {
    reg x = 0;
    f(j, 1, N) if (!b[j] && (x == 0 || d[j] < d[x])) x = j;
    b[x] = 1;
    f(j, 1, N) d[j] = min(d[j], d[x] + a[x][j]);
  }
  ms(b, 0);
  b[1] = 1;
  register long long ans = 1;
  f(i, 2, N) {
    reg cnt = 0, t = 0;
    f(j, 2, N) if (!b[j] && (t == 0 || d[t] > d[j])) t = j;
    f(j, 1, N) if (b[j] && d[t] == d[j] + a[t][j]) cnt++;
    b[t] = 1;
    (ans *= cnt) %= P;
  }
  printf("%lld\n", ans);
}