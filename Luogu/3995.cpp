#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 100006;
int N, Q, tot, fa[SN][19], si[SN], dep[SN], son[SN], Head[SN], Next[SN << 1],
    Ver[SN << 1];

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
il void dfs1(int x, int pre, int depth) {
  fa[x][0] = pre;
  dep[x] = depth;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == pre) continue;
    dfs1(y, x, depth + 1);
  }
}
il void dfs2(int x, int pre) {
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == pre) continue;
    dfs2(y, x);
    si[x] += si[y];
    if (si[y] >= si[son[x]]) son[x] = y;
  }
}
il void init() {
  dfs1(1, 0, 1);
  f(j, 1, 18) f(i, 1, N) fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
il int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (reg i = 18; i >= 0; i--)
    if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
  if (x == y) return x;
  for (reg i = 18; i >= 0; i--)
    if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

int main() {
  scanf("%d%d", &N, &Q);
  f(i, 2, N) {
    reg u, v;
    scanf("%d%d", &u, &v);
    add(u, v), add(v, u);
  }
  init();
  f(i, 1, Q) {
    reg u, v;
    scanf("%d%d", &u, &v);
    reg f = lca(u, v);
    if (fa[u][0] != f) si[u]++, si[f]--;
    if (fa[v][0] != f) si[v]++, si[f]--;
  }
  dfs2(1, 0);
  f(i, 1, N) printf("%d\n", son[i]);
}