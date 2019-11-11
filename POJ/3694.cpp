#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;

const int SI = 100006;
int N, M, tot, dcc, num, tc, Head[SI], Ver[SI << 2], Next[SI << 2], dfn[SI],
    low[SI], d[SI], Hc[SI], Vc[SI << 2], Nc[SI << 2], c[SI], fa[SI][18], se[SI];
bool br[SI << 2];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

il void addc(const int &x, const int &y) {
  Vc[++tc] = y, Nc[tc] = Hc[x], Hc[x] = tc;
}

il void prework() {
  queue<int> q;
  q.push(1);
  d[1] = 1;
  while (q.size()) {
    const reg x = q.front();
    q.pop();
    for (reg i = Hc[x]; i; i = Nc[i]) {
      const reg &y = Vc[i];
      if (d[y]) continue;
      d[y] = d[x] + 1;
      fa[y][0] = x;
      f(j, 1, 17) fa[y][j] = fa[fa[y][j - 1]][j - 1];
      q.push(y);
    }
  }
}

int get(const int &x) { return se[x] == x ? x : se[x] = get(se[x]); }

il int LCA(int x, int y) {
  if (d[x] < d[y]) swap(x, y);
  for (reg j = 17; j >= 0; j--)
    if (d[fa[x][j]] >= d[y]) x = fa[x][j];
  if (x == y) return x;
  for (reg j = 17; j >= 0; j--)
    if (fa[x][j] != fa[y][j]) x = fa[x][j], y = fa[y][j];
  return fa[x][0];
}

void tarjan(const int &x, const int &in_edge) {
  low[x] = dfn[x] = ++num;
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (!dfn[y]) {
      tarjan(y, i);
      low[x] = min(low[x], low[y]);
      if (low[y] > dfn[x]) br[i] = br[i ^ 1] = 1;
    } else if (i != (in_edge ^ 1))
      low[x] = min(low[x], dfn[y]);
  }
}

void dfs(const int &x) {
  c[x] = dcc;
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (c[y] || br[i]) continue;
    dfs(y);
  }
}

int main() {
  for (int cc = 1; 1; cc++) {
    scanf("%d%d", &N, &M);
    if (N == 0 || M == 0) break;
    ms(Head, 0), ms(Hc, 0), ms(br, 0), ms(dfn, 0), ms(c, 0), ms(d, 0);
    tot = 1;
    f(i, 1, M) {
      reg x, y;
      scanf("%d%d", &x, &y);
      add(x, y), add(y, x);
    }
    dcc = num = 0;
    f(i, 1, N) if (!dfn[i]) tarjan(i, 0);
    f(i, 1, N) if (!c[i]) { ++dcc, dfs(i); }
    tc = 1;
    f(i, 2, tot) {
      const reg &x = Ver[i ^ 1], &y = Ver[i];
      if (c[x] == c[y]) continue;
      addc(c[x], c[y]);
    }
    prework();
    f(i, 1, dcc) se[i] = i;
    reg Q, ans = dcc - 1;
    scanf("%d", &Q);
    printf("Case %d:\n", cc);
    f(i, 1, Q) {
      reg x, y, p;
      scanf("%d%d", &x, &y);
      x = c[x], y = c[y];
      // if (x == y) goto pr;
      p = LCA(x, y);
      for (x = get(x); d[x] > d[p]; x = get(x)) se[x] = fa[x][0], ans--;
      for (y = get(y); d[y] > d[p]; y = get(y)) se[y] = fa[y][0], ans--;
      // pr:
      printf("%d\n", ans);
    }
    puts("");
  }
}