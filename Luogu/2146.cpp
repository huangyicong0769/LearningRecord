#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 1e5 + 6;
int N, Q, cnt, dfn[SN], size[SN], son[SN], dep[SN], top[SN], fa[SN],  //
    tot, Head[SN], Next[SN << 1], Ver[SN << 1];                       //
struct SegmentationTreeNode {
  int sum, lazy;
} stn[SN << 2];

class SegmentationTree {
#define lc p << 1
#define rc p << 1 | 1
#define mid ((l + r) >> 1)
  SegmentationTreeNode *n = stn;
  il void pushDown(const int &p, const int &l, const int &r) {
    if (n[p].lazy == -1) return;
    n[lc].sum = (mid - l + 1) * n[p].lazy;
    n[rc].sum = (r - mid) * n[p].lazy;
    n[lc].lazy = n[rc].lazy = n[p].lazy;
    n[p].lazy = -1;
  }

 public:
  SegmentationTree() {}
  void build(int p, int l, int r) {
    n[p].sum = 0, n[p].lazy = -1;
    if (l == r) return;
    build(lc, l, mid);
    build(rc, mid + 1, r);
  }
  void modify(int p, int l, int r, const int &x, const int &y, const int &k) {
    if (x <= l && r <= y) {
      n[p].sum = (r - l + 1) * k;
      n[p].lazy = k;
      return;
    }
    pushDown(p, l, r);
    if (x <= mid) modify(lc, l, mid, x, y, k);
    if (mid < y) modify(rc, mid + 1, r, x, y, k);
    n[p].sum = n[lc].sum + n[rc].sum;
  }
  const int &sum = stn[1].sum;
#undef lc
#undef rc
#undef mid
} t;

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void dfs1(int x, int d) {
  // cout << x << endl;
  dep[x] = d;
  size[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    // if (y == fa[x]) continue;
    dfs1(y, d + 1);
    size[x] += size[y];
    if (size[y] > size[son[x]]) son[x] = y;
  }
}
void dfs2(int x, int t) {
  dfn[x] = ++cnt;
  top[x] = t;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (/* y == fa[x] ||  */ y == son[x]) continue;
    dfs2(y, y);
  }
}
il void chainModify(int x, int y, int k) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    t.modify(1, 1, cnt, dfn[top[x]], dfn[x], k);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  t.modify(1, 1, cnt, dfn[y], dfn[x], k);
}

int main() {
  scanf("%d", &N);
  f(i, 2, N) {
    scanf("%d", &fa[i]);
    ++fa[i];
    add(fa[i], i);
  }
  dfs1(1, 1), dfs2(1, 1), t.build(1, 1, cnt);
  scanf("%d", &Q);
  f(i, 1, Q) {
    char ch[10];
    reg a, t1 = t.sum;
    scanf("%s%d", ch, &a);
    a++;
    if (ch[0] == 'i') chainModify(1, a, 1);
    if (ch[0] == 'u') t.modify(1, 1, cnt, dfn[a], dfn[a] + size[a] - 1, 0);
    printf("%d\n", abs(t.sum - t1));
  }
}