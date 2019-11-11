#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define maxn 300030
using namespace std;
int n, m;
void get(int &x) {
  x = 0;
  bool b = 0;
  char c = getchar();
  while ((c < '0' || c > '9') && c != '-') c = getchar();
  if (c == '-') b = 1, c = getchar();
  while (c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
  if (b == 1) x = -x;
}
struct LCT {
  bool s[maxn];
  int top;
  struct treap {
    int l, r, fa, k, pre, v, x;
    bool p;
  } t[maxn];
  struct node {
    int x, y;
  };
  void init() {
    srand((unsigned long long)new char);
    for (int i = 1; i <= n; ++i) t[i].k = rand();
  }
  inline bool isroot(int o) {
    return (t[t[o].fa].l != o && t[t[o].fa].r != o) || !t[o].fa;
  }
  inline void pushdown(int o) {
    if (t[o].p) {
      t[o].p = 0;
      swap(t[o].l, t[o].r);
      t[t[o].l].p ^= 1, t[t[o].r].p ^= 1;
    }
  }
  inline void updata(int o) {
    t[o].x = t[o].v ^ t[t[o].l].x ^ t[t[o].r].x;
    if (t[o].l) t[t[o].l].fa = o;
    if (t[o].r) t[t[o].r].fa = o;
  }
  int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (t[x].k < t[y].k) {
      pushdown(x);
      t[x].r = merge(t[x].r, y);
      updata(x);
      return x;
    } else {
      pushdown(y);
      t[y].l = merge(x, t[y].l);
      updata(y);
      return y;
    }
  }
  int findroot(int o) {
    top = 0;
    while (!isroot(o)) {
      s[++top] = (t[t[o].fa].l == o);
      o = t[o].fa;
    }
    return o;
  }
  int findleft(int o) {
    o = findroot(o);
    pushdown(o);
    while (t[o].l) {
      o = t[o].l;
      pushdown(o);
    }
    return o;
  }
  node split(int o) {
    node tmp;
    if (!top) {
      pushdown(o);
      tmp = (node){o, t[o].r};
      t[o].r = 0;
      updata(o);
      return tmp;
    }
    bool d = s[top--];
    d ^= t[o].p;
    pushdown(o);
    if (d) {
      tmp = split(t[o].l);
      t[o].l = tmp.y;
      updata(o);
      return (node){tmp.x, o};
    } else {
      tmp = split(t[o].r);
      t[o].r = tmp.x;
      updata(o);
      return (node){o, tmp.y};
    }
  }
  int access(int o) {
    int last = 0;
    while (o) {
      node tmp = split(findroot(o));
      t[findleft(last)].pre = 0;
      last = merge(tmp.x, last);
      t[findleft(tmp.y)].pre = o;
      o = t[findleft(last)].pre;
    }
    return last;
  }
  int root(int o) { return findleft(access(o)); }
  void changeroot(int o) { t[access(o)].p ^= 1; }
  void link(int x, int y) {
    changeroot(x);
    t[x].pre = y;
  }
  void cut(int x, int y) {
    changeroot(x);
    access(y), access(x);
    t[y].pre = 0;
  }
  int query(int x, int y) {
    changeroot(x);
    access(y);
    node tmp = split(findroot(y));
    int ans = t[tmp.x].x;
    merge(tmp.x, tmp.y);
    return ans;
  }
  void change(int o, int v) {
    changeroot(o);
    node tmp = split(findroot(o));
    t[o].v = v;
    merge(tmp.x, tmp.y);
  }
} lct;
void init() {
  get(n), get(m);
  lct.init();
  for (int i = 1; i <= n; ++i) {
    get(lct.t[i].v);
    lct.t[i].x = lct.t[i].v;
  }
}
void solve() {
  while (m--) {
    int opt, x, y;
    get(opt), get(x), get(y);
    if (!opt)
      printf("%d\n", lct.query(x, y));
    else if (opt == 1 && lct.root(x) != lct.root(y))
      lct.link(x, y);
    else if (opt == 2)
      lct.cut(x, y);
    else if (opt == 3)
      lct.change(x, y);
  }
}
int main() {
  init();
  solve();
  return 0;
}