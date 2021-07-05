#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 1006;
int d[SN], f[SN], g[SN], a[SN], N;

il int read() {
  reg x = 0;
}

bool __cmp(const int &a, const int &b) {}

int main() {
  N = read();
  d[1] = a[1] = 1;
  g[1] = g[0] = N;
  f(i, 2, N) {
    f[i] = read();
    d[i] = d[f[i]] + 1;
    a[i] = i;
  }
  sort(a + 1, a + 1 + N, __cmp);
  reg ans = 0;
  f(i, 1, N) {
    reg x = a[i], y = f[x], z = f[y];
    g[i] = min({g[i], g[y] + 1, g[z] + 2});
    if (g[i] > 1) {
      ans++;
      g[i] = 0;
      g[x] = min({g[x], 1});
      g[y] = min({g[y], 2});
    }
  }
  printf("%d\n", ans);
}