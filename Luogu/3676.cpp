#include <cstdio>
#include <iostream>
using namespace std;
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
#define il inline

typedef long long ll;

const int SN = 200006;
int N, Q,                                        //
    tot, Head[SN], Next[SN << 1], Ver[SN << 1],  //
    cnt, dfn[SN], size[SN], top[SN], son[SN], dep[SN], fa[SN];
ll a[SN], b[SN], sa;

struct SegmentationTreeNode {
  ll s, s2, lazy;
} _stn[SN << 2];

class SegmentationTree {
#define lc p << 1
#define rc p << 1 | 1
#define mid (l + r >> 1)
  SegmentationTreeNode *n = _stn;

  il void mark(int p, int l, int r) {
    if (l == r) {
      n[p].s = n[p].lazy + b[l];
      n[p].s2 = n[p].s * n[p].s;
      return;
    }
    n[p].s = n[lc].s + n[rc].s + (r - l + 1) * n[p].lazy;
    n[p].s2 = n[lc].s2 + n[rc].s2 + n[p].lazy * n[p].lazy * (r - l + 1) +
              2 * n[p].lazy * (n[lc].s + n[rc].s);
  }

  il void pushDown(int p, int l, int r) {
    if (l == r)
      b[l] += n[p].lazy;
    else
      n[lc].lazy += n[p].lazy, n[rc].lazy += n[p].lazy;
    n[p].lazy = 0;
  }

 public:
  SegmentationTree() {}

  void build(int p, int l, int r) {
    if (l != r) build(lc, l, mid), build(rc, mid + 1, r);
    mark(p, l, r);
  }

  void modify(int p, int l, int r, int x, int y, ll k) {
    if (y < l || r < x) return;
    if (x <= l && r <= y)
      n[p].lazy += k;
    else
      modify(lc, l, mid, x, y, k), modify(rc, mid + 1, r, x, y, k);
    mark(p, l, r);
  }

  void query(int p, int l, int r, int x, int y, ll &ans, ll &ans2) {
    mark(p, l, r);
    if (y < l || r < x) return;
    if (x <= l && r <= y) {
      // cout << l << ' ' << r << ' ' << x << ' ' << y << ' ' << n[p].s << ' '
      //      << n[p].s2 << endl;
      ans += n[p].s, ans2 += n[p].s2;
      return;
    }
    pushDown(p, l, r);
    query(lc, l, mid, x, y, ans, ans2);
    query(rc, mid + 1, r, x, y, ans, ans2);
  }
#undef lc
#undef rc
#undef mid
};

il ll read() {
  reg ll x = 0, f = 1;
  reg char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    if (ch == '-') f = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x * f;
}

// extern il ll read();

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void dfs1(int x, int p, int d) {
  fa[x] = p, dep[x] = d, size[x] = 1;
  for (reg int i = Head[x]; i; i = Next[i]) {
    reg int y = Ver[i];
    if (y == p) continue;
    dfs1(y, x, d + 1);
    size[x] += size[y];
    if (size[y] > size[son[x]]) son[x] = y;
  }
}

void dfs2(int x, int t) {
  dfn[x] = ++cnt, b[dfn[x]] = a[x], top[x] = t;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (reg int i = Head[x]; i; i = Next[i]) {
    reg int y = Ver[i];
    if (y == fa[x]) continue;
    if (y != son[x]) dfs2(y, y);
    b[dfn[x]] += b[dfn[y]];
  }
}

il ll chainQuery(int x) {
  SegmentationTree t;
  ll ans = 0, ss = 0, k = 0, tmp;
  t.query(1, 1, cnt, 1, cnt, tmp, ans);
  // cout << ans << endl;
  while (top[x] != top[1]) {
    k += dfn[x] - dfn[top[x]] + 1;
    t.query(1, 1, cnt, dfn[top[x]], dfn[x], ss, tmp);
    x = fa[top[x]];
  }
  k += dfn[x] - dfn[1];
  t.query(1, 1, cnt, dfn[1] + 1, dfn[x], ss, tmp);
  return ans + sa * (k * sa - 2 * ss);
}

il void chainModify(ll k, int x) {
  // cout << x << endl;
  SegmentationTree t;
  k -= a[x];
  a[x] += k;
  sa += k;
  while (x) {
    t.modify(1, 1, cnt, dfn[top[x]], dfn[x], k);
    // cout << dfn[top[x]] << ' ' << dfn[x] << ' ' << k << endl;
    x = fa[top[x]];
  }
}

int main() {
  scanf("%d%d", &N, &Q);
  f(i, 2, N) {
    reg int a = read(), b = read();
    add(a, b), add(b, a);
  }
  f(i, 1, N) a[i] = read();
  SegmentationTree t;
  dfs1(1, 0, 1), dfs2(1, 1), sa = b[dfn[1]], t.build(1, 1, cnt);
  // for (int i = 1; i <= N; i++) printf("%d ", dfn[i]);
  // puts("");
  // for (int i = 1; i <= N; i++) printf("%d ", b[dfn[i]]);
  // puts("");
  // cout << sa << endl;
  f(i, 1, Q) {
    if (read() == 1)
      chainModify(read(), read());
    else
      printf("%lld\n", chainQuery(read()));
  }
}