#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define pir pair<int, int>
#define il inline

const int SN = 3e5 + 6;

class LCT {
  struct Treap {
    int v, w, ch[2], fa, pre, d;
    bool fl;
  } t[SN];
  int tot, top;
  bool st[SN];
  il void update(const int &p) {
    t[p].d = t[p].v ^ t[t[p].ch[0]].d ^ t[t[p].ch[1]].d;
    if (t[p].ch[0]) t[t[p].ch[0]].fa = p;
    if (t[p].ch[1]) t[t[p].ch[1]].fa = p;
  }
  il void push(const int &p) {
    if (t[p].fl) {
      swap(t[p].ch[0], t[p].ch[1]);
      if (t[p].ch[0]) t[t[p].ch[0]].fl ^= 1;
      if (t[p].ch[1]) t[t[p].ch[1]].fl ^= 1;
      t[p].fl = 0;
    }
  }
  il bool isRoot(const int &p) {
    return t[p].fa == 0 || (t[t[p].fa].ch[0] != p && t[t[p].fa].ch[1] != p);
  }
  il int findRoot(int p) {
    for (top = 0; !isRoot(p); p = t[p].fa/* , cout << "        " << p << endl */)
      st[++top] = (t[t[p].fa].ch[0] == p);
    return p;
  }
  il int findLeft(int p) {
    // cout << "   findLeft " << p << endl;
    for (p = findRoot(p), push(p)/* , cout << "     " << p << endl */; t[p].ch[0];
         p = t[p].ch[0], push(p)/* , cout << "     " << p << endl */)
      ;
    // cout << "   findLeft ended" << endl;
    return p;
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (t[l].w < t[r].w) {
      push(l);
      t[l].ch[1] = merge(t[l].ch[1], r);
      update(l);
      return l;
    } else {
      push(r);
      t[r].ch[0] = merge(l, t[r].ch[0]);
      update(r);
      return r;
    }
  }
  void split(int p, int &l, int &r) {
    // cout << "  split " << p << ' ' << l << ' ' << r << endl;
    if (!top) {
      push(p);
      l = p, r = t[p].ch[1];
      t[p].ch[1] = 0;
      update(p);
      return;
    }
    bool fl = st[top--] ^ t[p].fl;
    push(p);
    if (fl)
      r = p, split(t[p].ch[0], l, t[p].ch[0]);
    else
      l = p, split(t[p].ch[1], t[p].ch[1], r);
    update(p);
  }
  il int access(int p) {
    reg last = 0;
    // cout << "  access " << p << endl;
    for (; p; p = t[findLeft(last)].pre) {
      reg r1, r2;
      split(findRoot(p), r1, r2);
      // cout << "  split ended" << endl;
      t[findLeft(last)].pre = 0;
      last = merge(r1, last);
      // cout << "  merge ended" << endl;
      t[findLeft(r2)].pre = p;
    }
    // cout << "  access ended" << endl;
    return last;
  }
  il void makeRoot(int p) { t[access(p)].fl ^= 1; }

 public:
  LCT() {
    tot = top = 0;
    // cout << "?" << endl;
  }
  il void init(const int &p, const int &v) {
    t[p].d = t[p].v = v, t[p].w = rand(),
    t[p].fa = t[p].pre = t[p].fl = t[p].ch[0] = t[p].ch[1] = 0;
  }
  il int root(const int &p) { return findLeft(access(p)); }
  il int query(const int &p, const int &q) {
    makeRoot(p);
    access(q);
    reg r1, r2;
    split(findRoot(q), r1, r2);
    reg ans = t[r1].d;
    merge(r1, r2);
    return ans;
  }
  il void link(const int &p, const int &q) {
    if (root(p) == root(q)) return;
    makeRoot(p);
    t[p].pre = q;
  }
  il void cut(const int &p, const int &q) {
    makeRoot(p);
    access(q), access(p);
    t[q].pre = 0;
  }
  il void set(const int &p, const int &v) {
    makeRoot(p);
    reg r1, r2;
    split(findRoot(p), r1, r2);
    t[p].v = v;
    merge(r1, r2);
  }
  il void out(int p) {
    if (!p) return;
    push(p);
    out(t[p].ch[0]);
    printf("%d ", t[p].v);
    out(t[p].ch[1]);
  }
} lct;

int main() {
  // freopen("input.txt", "r", stdin);
  // cout << "!" << endl;
  reg N, M;
  scanf("%d%d", &N, &M);
  f(i, 1, N) {
    reg a;
    scanf("%d", &a);
    lct.init(i, a);
  }
  // cout << "!" << endl;
  f(i, 1, M) {
    reg op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    // cout << ' ' << i << ' ' << op << ' ' << x << ' ' << y << endl;
    if (op == 0) printf("%d\n", lct.query(x, y));
    if (op == 1) lct.link(x, y);
    if (op == 2) lct.cut(x, y);
    if (op == 3) lct.set(x, y);
  }
}
