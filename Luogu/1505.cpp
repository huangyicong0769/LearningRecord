#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 200006, INF = (1 << 31) - 1;
int N, M, pw[SN], bridgeId[SN],                                  //
    tot, Head[SN], Ver[SN << 1], Next[SN << 1], Weigh[SN << 1],  //
    cnt, dfn[SN], si[SN], son[SN], dep[SN], fa[SN], top[SN];
struct SegmentationTreeNode {
  int sum, minn, maxn;
  bool lazy;
} _stn[SN << 2];

class SegmentationTree {
#define lc p << 1
#define rc p << 1 | 1
  SegmentationTreeNode *node = _stn;
  il void mark(const int &p) {
    swap(node[p].minn, node[p].maxn);
    node[p].minn *= -1, node[p].maxn *= -1, node[p].sum *= -1;
  }
  il void pushUp(const int &p) {
    pushDown(lc), pushDown(rc);
    node[p].sum = node[lc].sum + node[rc].sum;
    node[p].maxn = max(node[lc].maxn, node[rc].maxn);
    node[p].minn = min(node[lc].minn, node[rc].minn);
  }
  il void pushDown(const int &p) {
    if (!node[p].lazy) return;
    mark(p);
    node[p].lazy = 0, node[lc].lazy ^= 1, node[rc].lazy ^= 1;
  }

 public:
  SegmentationTree() {}
  void build(int p, int l, int r) {
    if (l == r) {
      node[p].maxn = node[p].minn = node[p].sum = pw[l];
      return;
    }
    reg mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushUp(p);
  }
  void modify(int p, int l, int r, const int &x, const int &k) {
    pushDown(p);
    if (l == r) {
      node[p].maxn = node[p].minn = node[p].sum = k;
      return;
    }
    reg mid = (l + r) >> 1;
    if (x <= mid) modify(lc, l, mid, x, k);
    if (mid < x) modify(rc, mid + 1, r, x, k);
    pushUp(p);
  }
  void flip(int p, int l, int r, const int &x, const int &y) {
    if (x <= l && r <= y) {
      node[p].lazy ^= 1;
      return;
    }
    pushDown(p);
    reg mid = (l + r) >> 1;
    if (x <= mid) flip(lc, l, mid, x, y);
    if (mid < y) flip(rc, mid + 1, r, x, y);
    pushUp(p);
  }
  int queryMin(int p, int l, int r, const int &x, const int &y) {
    pushDown(p);
    if (x <= l && r <= y) return node[p].minn;
    reg mid = (l + r) >> 1, ret = INF;
    if (x <= mid) ret = min(ret, queryMin(lc, l, mid, x, y));
    if (mid < y) ret = min(ret, queryMin(rc, mid + 1, r, x, y));
    return ret;
  }
  int queryMax(int p, int l, int r, const int &x, const int &y) {
    pushDown(p);
    // printf("%d %d %d %d %d\n", l, r, x, y, node[p].maxn);
    if (x <= l && r <= y) return node[p].maxn;
    reg mid = (l + r) >> 1, ret = -INF;
    if (x <= mid) ret = max(ret, queryMax(lc, l, mid, x, y));
    if (mid < y) ret = max(ret, queryMax(rc, mid + 1, r, x, y));
    return ret;
  }
  int querySum(int p, int l, int r, const int &x, const int &y) {
    // cout << l << ' ' << r << ' ' << x << ' ' << y << endl;
    pushDown(p);
    if (x <= l && r <= y) return /*printf(" %d\n", node[p].sum), */ node[p].sum;
    reg mid = (l + r) >> 1, ret = 0;
    if (x <= mid) ret += querySum(lc, l, mid, x, y);
    if (mid < y) ret += querySum(rc, mid + 1, r, x, y);
    return ret;
  }
#undef lc
#undef rc
} t;

il void add(int x, int y, int z) {
  Ver[++tot] = y, Weigh[tot] = z, Next[tot] = Head[x], Head[x] = tot;
}
void dfs1(int x, int pre, int d) {
  fa[x] = pre, dep[x] = d, si[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == pre) continue;
    dfs1(y, x, d + 1);
    si[x] += si[y];
    if (si[y] > si[son[x]]) son[x] = y;
  }
}
void dfs2(int x, int t) {
  dfn[x] = ++cnt;
  top[x] = t;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == fa[x]) continue;
    if (y != son[x]) dfs2(y, y);
    pw[dfn[y]] = Weigh[i];
    bridgeId[i >> 1] = dfn[y];
    // printf("dfs2(%d, %d), dfn[y] = %d, Weigh[i] = %d, EdgeNum = %d\n", x, t,
    //        dfn[y], Weigh[i], i >> 1);
  }
}
il void chainFlip(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    t.flip(1, 1, cnt, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  t.flip(1, 1, cnt, dfn[y] + 1, dfn[x]);
}
il int chainQueryMin(int x, int y) {
  reg ret = INF;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ret = min(ret, t.queryMin(1, 1, cnt, dfn[top[x]], dfn[x]));
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  ret = min(ret, t.queryMin(1, 1, cnt, dfn[y] + 1, dfn[x]));
  return ret;
}
il int chainQueryMax(int x, int y) {
  reg ret = -INF;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ret = max(ret, t.queryMax(1, 1, cnt, dfn[top[x]], dfn[x]));
    // printf("x = %d, top[x] = %d ret = %d\n", x, top[x], ret);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) swap(x, y);
  ret = max(ret, t.queryMax(1, 1, cnt, dfn[y] + 1, dfn[x]));
  // printf("x = %d, y = %d ret = %d\n", x, y, ret);
  return ret;
}
il int chainQuerySum(int x, int y) {
  reg ret = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ret += t.querySum(1, 1, cnt, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  // cout << "C" << endl;
  if (dep[x] < dep[y]) swap(x, y);
  ret += t.querySum(1, 1, cnt, dfn[y] + 1, dfn[x]);
  // cout << "D" << endl;
  return ret;
}

int main() {
  // freopen("./data/1505/1.in", "r", stdin);
  // freopen("output.txt", "w", stdout);
  scanf("%d", &N);
  tot = 1;
  f(i, 2, N) {
    reg a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    a++, b++;
    add(a, b, c), add(b, a, c);
  }
  dfs1(1, 0, 1);
  dfs2(1, 1);
  // f(i, 1, N) printf("%d ", i);
  // puts("");
  // f(i, 1, N) printf("%d ", dfn[i]);
  // cout << endl;
  // f(i, 1, N) printf("%d ", son[i]);
  // cout << endl;
  t.build(1, 1, cnt);
  scanf("%d", &M);
  f(i, 1, M) {
    string s;
    reg a, b;
    cin >> s >> a >> b;
    a++, b++;
    if (s == "C") t.modify(1, 1, cnt, bridgeId[a - 1], b - 1);
    if (s == "N") chainFlip(a, b);
    if (s == "SUM") printf("%d\n", chainQuerySum(a, b));
    if (s == "MAX") printf("%d\n", chainQueryMax(a, b));
    if (s == "MIN") printf("%d\n", chainQueryMin(a, b));
  }
}