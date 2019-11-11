#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 1e5 + 6;
int N, M, oc[SN], pc[SN],                        //
    tot, Head[SN], Next[SN << 1], Ver[SN << 1],  //
    cnt, dfn[SN], size[SN], fa[SN], son[SN], top[SN], dep[SN];
struct SegmentationTreeNode {
  int cnt, lsc, rsc, lazy;
} stn[SN << 2];

class SegmentationTree {
#define mid ((l + r) >> 1)
#define lc p << 1
#define rc p << 1 | 1
  SegmentationTreeNode *n = stn;
  il void pushDown(int p) {
    if (!n[p].lazy) return;
    n[lc].cnt = n[rc].cnt = 1;
    n[lc].lsc = n[lc].rsc = n[rc].lsc = n[rc].rsc = n[p].lazy;
    n[lc].lazy = n[rc].lazy = n[p].lazy;
    n[p].lazy = 0;
  }
  il void update(int p) {
    n[p].lsc = n[lc].lsc, n[p].rsc = n[rc].rsc;
    n[p].cnt = n[lc].cnt + n[rc].cnt;
    if (n[lc].rsc == n[rc].lsc) n[p].cnt--;
  }

 public:
  SegmentationTree() {}
  void build(int p, int l, int r) {
    if (l == r) {
      n[p].lsc = n[p].rsc = pc[l];
      n[p].cnt = 1, n[p].lazy = 0;
      return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    update(p);
  }
  void modify(int p, int l, int r, int x, int y, int k) {
    if (x <= l && r <= y) {
      n[p].cnt = 1, n[p].lazy = n[p].lsc = n[p].rsc = k;
      return;
    }
    pushDown(p);
    if (x <= mid) modify(lc, l, mid, x, y, k);
    if (mid < y) modify(rc, mid + 1, r, x, y, k);
    update(p);
  }
  int query(int p, int l, int r, int x, int y) {
    // cout << "   " << l << ' ' << r << ' ' << n[p].cnt << ' ' << x << ' ' << y
    // << endl;
    if (x <= l && r <= y) return n[p].cnt;
    pushDown(p);
    reg ret = 0;
    if (x <= mid) ret = query(lc, l, mid, x, y);
    if (mid < y) {
      if (ret != 0 && n[lc].rsc == n[rc].lsc) ret--;
      ret += query(rc, mid + 1, r, x, y);
    }
    return ret;
  }
  int query(int p, int l, int r, int k) {
    if (l == r) return n[p].lsc;
    pushDown(p);
    if (k <= mid) return query(lc, l, mid, k);
    if (mid < k) return query(rc, mid + 1, r, k);
  }
#undef lc
#undef rc
#undef mid
} tr;

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void dfs1(int x, int p, int d) {
  fa[x] = p, size[x] = 1, dep[x] = d;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == p) continue;
    dfs1(y, x, d + 1);
    size[x] += size[y];
    if (size[y] > size[son[x]]) son[x] = y;
  }
}
void dfs2(int x, int t) {
  dfn[x] = ++cnt, pc[dfn[x]] = oc[x], top[x] = t;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == son[x] || y == fa[x]) continue;
    dfs2(y, y);
  }
}
il void chainModify(int x, int y, int k) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    tr.modify(1, 1, cnt, dfn[top[x]], dfn[x], k);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  // cout << dfn[x] << ' ' << dfn[y] << endl;
  tr.modify(1, 1, cnt, dfn[y], dfn[x], k);
}
il int chainQuery(int x, int y) {
  reg ret = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    // cout << ' ' << x << ' ' << y << endl;
    ret += tr.query(1, 1, cnt, dfn[top[x]], dfn[x]);
    // cout << "  " << top[x] << ' ' << fa[top[x]] << ' '
    //      << tr.query(1, 1, cnt, dfn[top[x]], dfn[x]) << ' '
    //      << tr.query(1, 1, cnt, dfn[top[x]]) << ' '
    //      << tr.query(1, 1, cnt, dfn[fa[top[x]]]) << endl;
    if (tr.query(1, 1, cnt, dfn[top[x]]) ==
        tr.query(1, 1, cnt, dfn[fa[top[x]]]))
      ret-- /* , cout << '!' << endl */;
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  // cout << ' ' << x << ' ' << y << endl;
  // cout << "  " << ret << endl << tr.query(1, 1, cnt, dfn[y], dfn[x]) << endl;
  ret += tr.query(1, 1, cnt, dfn[y], dfn[x]);
  return ret;
}

int main() {
  // freopen("output.txt", "w", stdout);
  scanf("%d%d", &N, &M);
  f(i, 1, N) scanf("%d", &oc[i]);
  f(i, 2, N) {
    reg u, v;
    scanf("%d%d", &u, &v);
    add(u, v), add(v, u);
  }
  dfs1(1, 0, 1), dfs2(1, 1), tr.build(1, 1, cnt);
  // f(i, 1, cnt) printf("%d ", dfn[i]); puts("");
  // f(i, 1, cnt) printf("%d ", pc[dfn[i]]); puts("");
  // f(i, 1, cnt) printf("%d ", tr.query(1, 1, cnt, dfn[i]));
  // puts("\n");
  f(i, 1, M) {
    char ch[2];
    reg a, b, c;
    scanf("%s", ch);
    // f(i, 1, cnt) printf("%d ", tr.query(1, 1, cnt, dfn[i])); puts("");
    if (ch[0] == 'Q') scanf("%d%d", &a, &b), printf("%d\n", chainQuery(a, b));
    if (ch[0] == 'C') scanf("%d%d%d", &a, &b, &c), chainModify(a, b, c);
    // f(i, 1, cnt) printf("%d ", tr.query(1, 1, cnt, dfn[i])); puts("\n");
  }
}