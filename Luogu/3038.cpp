#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 100006;
int N, M, tot, cnt, son[SN], dep[SN], fa[SN], si[SN], dfn[SN], top[SN],
    Head[SN], Next[SN << 1], Ver[SN << 1];
struct SegmentationTreeNode {
  int w, lazy;
} stn[SN << 2];

class SegmentationTree {
#define lc p << 1
#define rc p << 1 | 1
  SegmentationTreeNode *a = stn;
  il void mark(const int &p, const int &l, const int &r, const int &k) {
    a[p].w += (r - l + 1) * k;
    a[p].lazy += k;
  }
  il void pushDown(const int &p, const int &l, const int &r) {
    if (!a[p].lazy) return;
    reg mid = (l + r) >> 1;
    mark(lc, l, mid, a[p].lazy);
    mark(rc, mid + 1, r, a[p].lazy);
    a[p].lazy = 0;
  }

 public:
  SegmentationTree() {}
  void build(int p, int l, int r) {
    if (l == r) {
      a[p].w = 0;
      return;
    }
    reg mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    a[p].w = a[lc].w + a[rc].w;
  }
  int query(int p, int l, int r, const int &x, const int &y) {
    if (x <= l && r <= y) return a[p].w;
    pushDown(p, l, r);
    reg mid = (l + r) >> 1, ret = 0;
    if (mid >= x) ret += query(lc, l, mid, x, y);
    if (mid < y) ret += query(rc, mid + 1, r, x, y);
    return ret;
  }
  void modify(int p, int l, int r, const int &x, const int &y, const int &k) {
    if (x <= l && r <= y) {
      mark(p, l, r, k);
      return;
    }
    pushDown(p, l, r);
    reg mid = (l + r) >> 1;
    if (x <= mid) modify(lc, l, mid, x, y, k);
    if (mid < y) modify(rc, mid + 1, r, x, y, k);
    a[p].w = a[lc].w + a[rc].w;
  }
#undef lc
#undef rc
} tr;

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void dfs1(int x, int pre, int d) {
  dep[x] = d, fa[x] = pre, si[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == pre) continue;
    dfs1(y, x, d + 1);
    si[x] += si[y];
    if (!son[x] || si[y] > si[son[x]]) son[x] = y;
  }
}
void dfs2(int x, int t) {
  dfn[x] = ++cnt;
  top[x] = t;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == fa[x] || y == son[x]) continue;
    dfs2(y, y);
  }
}
il int query(int x, int y) {
  reg ans = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ans += tr.query(1, 1, cnt, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  ans += tr.query(1, 1, cnt, dfn[y] + 1, dfn[x]);
  return ans;
}
il void modify(int x, int y, int k) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    tr.modify(1, 1, cnt, dfn[top[x]], dfn[x], k);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  tr.modify(1, 1, cnt, dfn[y] + 1, dfn[x], k);
}

int main() {
  scanf("%d%d", &N, &M);
  f(i, 2, N) {
    reg a, b;
    scanf("%d%d", &a, &b);
    add(a, b), add(b, a);
  }
  dfs1(1, 0, 1);
  dfs2(1, 1);
  tr.build(1, 1, cnt);
  f(i, 1, M) {
    char ch;
    reg a, b;
    cin >> ch >> a >> b;
    if (ch == 'Q') printf("%d\n", query(a, b));
    if (ch == 'P') modify(a, b, 1);
  }
}