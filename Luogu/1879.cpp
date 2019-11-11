#include <cstdio>
#include <iostream>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t; i++)
using namespace std;

const int P = 100000000;
int M, N, f[13][1 << 12], w[13];
bool st[1 << 12];

int main() {
  scanf("%d%d", &N, &M);
  f(i, 1, N + 1) f(j, 0, M) {
    reg t;
    scanf("%d", &t);
    w[i] |= t << (M - j - 1);
  }
  f(i, 0, 1 << M) st[i] = (i & (i << 1)) == 0 && (i & (i >> 1)) == 0;
  f[0][0] = 1;
  f(i, 1, N + 1) {
    f(j, 0, 1 << M) if ((j & w[i]) == j && st[j]) {
      f[i][j] = 0;
      f(k, 0, 1 << M) if ((k & w[i - 1]) == k && st[k] && (k & j) == 0)
          f[i][j] = (f[i][j] + f[i - 1][k]) % P;
    }
  }
  reg ans = 0;
  f(i, 0, 1 << M) ans = (ans + f[N][i]) % P;
  printf("%d\n", ans);
}