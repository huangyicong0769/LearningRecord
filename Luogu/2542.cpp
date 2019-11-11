#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 30006, SM = 100006, SQ = 40006;
int N, M, q[SQ][3], ans[SQ],                                       //
    tot, Head[SN], Next[SM << 1], Ver[SM << 1], illegal[SM << 1],  //
    cnt, dfn[SN], dep[SN], size[SN], son[SN], top[SN], fa[SN];

struct SegmentationTreeNode {
  int sum, lazy;
} n[SN << 2];

#define lc p << 1
#define rc p << 1 | 1
#define mid ((l + r) >> 1)
il void pushDown(int p, int l, int r) {
  if (!n[p].lazy) return;
  n[lc].sum = n[rc].sum = 0;
  n[lc].lazy = n[rc].lazy = 1;
  n[p].lazy = 0;
}

void build(int p, int l, int r) {
  if (l == r) {
    n[p].sum = 1;
    return;
  }
  build(lc, l, mid);
  build(rc, mid + 1, r);
  n[p].sum = n[lc].sum + n[rc].sum;
}

void modify(int p, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    n[p].sum = 0, n[p].lazy = 1;
    return;
  }
  pushDown(p, l, r);
  if (x <= mid) modify(lc, l, mid, x, y);
  if (mid < y) modify(rc, mid + 1, r, x, y);
  n[p].sum = n[lc].sum + n[rc].sum;
}

int query(int p, int l, int r, int x, int y) {
  if (x <= l && r <= y) return n[p].sum;
  pushDown(p, l, r);
  reg ret = 0;
  if (x <= mid) ret += query(lc, l, mid, x, y);
  if (mid < y) ret += query(rc, mid + 1, r, x, y);
  return ret;
}
#undef lc
#undef rc
#undef mid

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void chainModify(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    modify(1, 1, cnt, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  if (dfn[y] < dfn[x]) modify(1, 1, cnt, dfn[y] + 1, dfn[x]);
}

int chainQuery(int x, int y) {
  reg ret = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ret += query(1, 1, cnt, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  if (dfn[y] < dfn[x]) ret += query(1, 1, cnt, dfn[y] + 1, dfn[x]);
  return ret;
}

void dfs1(int x) {
  size[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (size[y] || illegal[i]) continue;
    dep[y] = dep[x] + 1, fa[y] = x;
    dfs1(y);
    size[x] += size[y];
    if (size[y] > size[son[x]]) son[x] = y;
  }
}

void dfs2(int x, int t) {
  dfn[x] = ++cnt, top[x] = t;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (x != fa[y] || y == son[x] || illegal[i]) continue;
    dfs2(y, y);
  }
}

void dfs3(int x) {
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (illegal[i]) continue;
    if (fa[y] == x) dfs3(y);
    if (y != fa[x] && dep[y] < dep[x]) chainModify(y, x);
  }
}

int main() {
  scanf("%d%d", &N, &M);
  tot = 1;
  f(i, 1, M) {
    reg a, b;
    scanf("%d%d", &a, &b);
    add(a, b), add(b, a);
  }
  reg c, tc = 0;
  for (scanf("%d", &c); c != -1; scanf("%d", &c)) {
    q[++tc][0] = c;
    scanf("%d%d", &q[tc][1], &q[tc][2]);
    if (c == 0)
      for (reg i = Head[q[tc][1]]; i; i = Next[i])
        if (Ver[i] == q[tc][2]) illegal[i] = illegal[i ^ 1] = 1;
  }
  dep[1] = 1, dfs1(1), dfs2(1, 1), build(1, 1, cnt), dfs3(1);
  // f(i, 1, N) printf("%d ", dfn[i]); puts("");
  for (reg i = tc; i; i--) {
    if (q[i][0] == 0)
      chainModify(q[i][1], q[i][2]);
    else
      ans[i] = chainQuery(q[i][1], q[i][2]);
  }
  // puts("----------");
  f(i, 1, tc) if (q[i][0] == 1) printf("%d\n", ans[i]);
  return 0;
}