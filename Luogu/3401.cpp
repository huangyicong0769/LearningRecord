#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

typedef long long ll;
const int SN = 30006;
int N, Q, aw[SN],                                               //
    tot, Head[SN], Next[SN << 1], Ver[SN << 1], Edge[SN << 1],  //
    cnt, dfn[SN], top[SN], son[SN], size[SN], dep[SN], fa[SN];
struct Node {
  ll xsum, sum, p[2][10], s[2][10];
  il Node merge(Node a, Node b) {
    register Node t = {0};
    t.xsum = a.xsum ^ b.xsum;
    t.sum = a.sum + b.sum;
    f(i, 0, 9) {
      f(k, 0, 1) t.sum += a.s[k][i] * b.p[k ^ 1][i] << i;
      reg bl = a.xsum >> i & 1, br = b.xsum >> i & 1;
      t.p[0][i] = a.p[0][i] + b.p[bl][i];
      t.p[1][i] = a.p[1][i] + b.p[bl ^ 1][i];
      t.s[0][i] = b.s[0][i] + a.s[br][i];
      t.s[1][i] = b.s[1][i] + a.s[br ^ 1][i];
    }
    return *this = t;
  }
} stn[SN << 2];

class SegmentationTree {
#define lc p << 1
#define rc p << 1 | 1
#define mid (l + r >> 1)
  Node *n = stn;

 public:
  SegmentationTree() {}

  void build(int p, int l, int r) {
    if (l == r) {
      n[p].sum = n[p].xsum = aw[l];
      f(i, 0, 9) {
        n[p].p[0][i] = n[p].s[0][i] = n[p].xsum >> i & 1 ^ 1;
        n[p].p[1][i] = n[p].s[1][i] = n[p].xsum >> i & 1;
      }
      return;
    }
    // cout << l << ' ' << r << endl;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    n[p].merge(n[lc], n[rc]);
  }

  void modify(int p, int l, int r, int x, int k) {
    if (l == r) {
      n[p].sum = n[p].xsum = k;
      f(i, 0, 9) {
        n[p].p[0][i] = n[p].s[0][i] = n[p].xsum >> i & 1 ^ 1;
        n[p].p[1][i] = n[p].s[1][i] = n[p].xsum >> i & 1;
      }
      return;
    }
    if (x <= mid) modify(lc, l, mid, x, k);
    if (mid < x) modify(rc, mid + 1, r, x, k);
    n[p].merge(n[lc], n[rc]);
  }

  Node query(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return n[p];
    if (y <= mid) return query(lc, l, mid, x, y);
    if (mid < x) return query(rc, mid + 1, r, x, y);
    Node tl = query(lc, l, mid, x, y), tr = query(rc, mid + 1, r, x, y);
    return tl.merge(tl, tr);
  }
#undef lc
#undef rc
#undef mid
};

il void add(int x, int y, int w) {
  Ver[++tot] = y, Next[tot] = Head[x], Edge[tot] = w, Head[x] = tot;
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
    reg y = Ver[i], z = Edge[i];
    if (y == fa[x]) continue;
    if (y != son[x]) dfs2(y, y);
    aw[dfn[y]] = z;
  }
}

il ll chainQuery(int x, int y) {
  if (x == y) return 0;
  SegmentationTree t;
  Node tl[50] = {0}, tr[50] = {0};
  reg pl = 0, pr = 0, tx = top[x], ty = top[y];
  while (tx != ty)
    if (dep[tx] > dep[ty]) {
      tl[++pl] = t.query(1, 1, cnt, dfn[tx], dfn[x]);
      x = fa[tx], tx = top[x];
    } else {
      tr[++pr] = t.query(1, 1, cnt, dfn[ty], dfn[y]);
      y = fa[ty], ty = top[y];
    }
  if (x != y)
    if (dfn[x] > dfn[y])
      tl[++pl] = t.query(1, 1, cnt, dfn[y] + 1, dfn[x]);
    else
      tr[++pr] = t.query(1, 1, cnt, dfn[x] + 1, dfn[y]);
  f(i, 2, pl) tl[1].merge(tl[i], tl[1]);
  f(i, 2, pr) tr[1].merge(tr[i], tr[1]);
  if (!pl) return tr[1].sum;
  if (!pr) return tl[1].sum;
  f(i, 0, 9) f(k, 0, 1) swap(tl[1].p[k][i], tl[1].s[k][i]);
  return tl[1].merge(tl[1], tr[1]).sum;
}

int main() {
  scanf("%d%d", &N, &Q);
  f(i, 2, N) {
    reg u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w), add(v, u, w);
  }
  SegmentationTree t;
  dfs1(1, 0, 1), dfs2(1, 1), t.build(1, 1, cnt);
  f(i, 1, Q) {
    reg op, u, v, w;
    scanf("%d%d%d", &op, &u, &v);
    if (op == 1) printf("%lld\n", chainQuery(u, v));
    if (op == 2) scanf("%d", &w), t.modify(1, 1, cnt, max(dfn[u], dfn[v]), w);
  }
}
