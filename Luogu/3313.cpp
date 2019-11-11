#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 10e5;
int N, Q, root[SN], w[SN], c[SN], num,           //
    tot, Head[SN], Next[SN << 1], Ver[SN << 1],  //
    cnt, dfn[SN], size[SN], top[SN], dep[SN], fa[SN], son[SN];
struct SegmentationTreeNode {
  int lc, rc, maxm, sum;
} n[SN << 2];

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void dfs1(int x, int p, int d) {
  fa[x] = p, dep[x] = d, size[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == p) continue;
    dfs1(y, x, d + 1);
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
    if (y == fa[x] || y == son[x]) continue;
    dfs2(y, y);
  }
}
void modify(int &p, int l, int r, int x, int w) {
  if (!p) p = ++num;
  n[p].sum += w, n[p].maxm = max(n[p].maxm, w);
  if (l == r) return;
  reg mid = l + r >> 1;
  if (x <= mid) modify(n[p].lc, l, mid, x, w);
  if (mid < x) modify(n[p].rc, mid + 1, r, x, w);
}
void remove(int &p, int l, int r, int x) {
  if (l == r) {
    n[p].maxm = n[p].sum = 0;
    return;
  }
  reg mid = l + r >> 1;
  if (x <= mid) remove(n[p].lc, l, mid, x);
  if (mid < x) remove(n[p].rc, mid + 1, r, x);
  n[p].sum = n[n[p].lc].sum + n[n[p].rc].sum;
  n[p].maxm = max(n[n[p].lc].maxm, n[n[p].rc].maxm);
}
int querySum(int p, int l, int r, int x, int y) {
  if (x <= l && r <= y) return n[p].sum;
  reg mid = l + r >> 1, ret = 0;
  if (x <= mid) ret += querySum(n[p].lc, l, mid, x, y);
  if (mid < y) ret += querySum(n[p].rc, mid + 1, r, x, y);
  return ret;
}
int queryMax(int p, int l, int r, int x, int y) {
  if (x <= l && r <= y) return n[p].maxm;
  reg mid = l + r >> 1, ret = (1 << 31) + 1;
  if (x <= mid) ret = max(ret, queryMax(n[p].lc, l, mid, x, y));
  if (mid < y) ret = max(ret, queryMax(n[p].rc, mid + 1, r, x, y));
  return ret;
}
int chainQuerySum(int x, int y, int c) {
  reg ret = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ret += querySum(root[c], 1, cnt, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  ret += querySum(root[c], 1, cnt, dfn[y], dfn[x]);
  return ret;
}
int chainQueryMax(int x, int y, int c) {
  reg ret = (1 << 31) + 1;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ret = max(ret, queryMax(root[c], 1, cnt, dfn[top[x]], dfn[x]));
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  ret = max(ret, queryMax(root[c], 1, cnt, dfn[y], dfn[x]));
  return ret;
}

int main() {
  // freopen("./data/3313/1.in", "r", stdin);
  // freopen("output.txt", "w", stdout);
  scanf("%d%d", &N, &Q);
  f(i, 1, N) scanf("%d%d", &w[i], &c[i]);
  f(i, 2, N) {
    reg x, y;
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  dfs1(1, 0, 1), dfs2(1, 1);
  f(i, 1, N) modify(root[c[i]], 1, cnt, dfn[i], w[i]);
  // f(i, 1, N) printf("%d ", querySum(root[c[i]], 1, cnt, dfn[i], dfn[i]));
  // puts("");
  f(i, 1, Q) {
    char ch[3];
    reg a, b;
    scanf("%s%d%d", ch, &a, &b);
    if (ch[1] == 'C') {
      remove(root[c[a]], 1, cnt, dfn[a]);
      modify(root[c[a] = b], 1, cnt, dfn[a], w[a]);
    }
    if (ch[1] == 'W') {
      remove(root[c[a]], 1, cnt, dfn[a]);
      modify(root[c[a]], 1, cnt, dfn[a], w[a] = b);
    }
    if (ch[1] == 'S') printf("%d\n", chainQuerySum(a, b, c[a]));
    if (ch[1] == 'M') printf("%d\n", chainQueryMax(a, b, c[a]));
  }
}