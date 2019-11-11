#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)

const int SN = 206;
int N, M, T, ans, x[SN], y[SN], a[SN],  //
    tot, Head[SN], Ver[SN * SN], Next[SN * SN], Edge[SN * SN];
bool in[SN];

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il bool check(int a, int b) {
  reg xmax = max(x[a], x[b]), xmin = min(x[a], x[b]),  //
      ymax = max(y[a], y[b]), ymin = min(y[a], y[b]);
  f(k, 1, M) if (k != a && k != b && xmin <= x[k] && x[k] <= xmax &&
                 ymin <= y[k] && y[k] <= ymax) return false;
  return true;
}

il int dis(int a, int b) { return abs(x[a] - x[b]) + abs(y[a] - y[b]); }

il void add(int x, int y, int z) {
  Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
}

il void dfs(int x, int t, int s) {
  if (t < 0) return;
  ans = max(ans, s);
  in[x] = 1;
  for (reg i = Head[x]; i; i = Next[i])
    if (!in[Ver[i]]) dfs(Ver[i], t - Edge[i], s + a[Ver[i]]);
  in[x] = 0;
}

int main() {
  N = read(), M = read() + 1, T = read();
  f(i, 1, M - 1) x[i] = read(), y[i] = read(), a[i] = read();
  x[M] = y[M] = a[M] = 0;
  f(i, 1, M) f(j, 1, M) if (i != j && check(i, j)) add(i, j, dis(i, j));
  dfs(M, T, 0);
  printf("%d\n", ans);
}