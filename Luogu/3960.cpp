#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define int ll
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline
typedef long long ll;

const int SN = 3e5 + 6;
int N, M, Q, tot, root[SN];
struct Node {
  int ch[2], w, l, r, si;
} treap[SN * 20];

il int newNode(int x, int y) {
  Node& a = treap[++tot];
  a.l = x, a.r = y;
  a.w = rand();
  a.si = y - x + 1;
  return tot;
}
il void update(int cur) {
  Node& a = treap[cur];
  a.si = treap[a.ch[0]].si + treap[a.ch[1]].si + a.r - a.l + 1;
}
int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (treap[x].w > treap[y].w) {
    treap[x].ch[1] = merge(treap[x].ch[1], y);
    update(x);
    return x;
  } else {
    treap[y].ch[0] = merge(x, treap[y].ch[0]);
    update(y);
    return y;
  }
}
il void splitNew(int cur, int k) {
  if (k >= treap[cur].r - treap[cur].l + 1) return;
  reg nr = newNode(treap[cur].l + k, treap[cur].r);
  treap[cur].r = treap[cur].l + k - 1;
  treap[cur].ch[1] = merge(nr, treap[cur].ch[1]);
  update(cur);
}
void split(int cur, int k, int& x, int& y) {
  if (!cur)
    x = y = 0;
  else {
    if (treap[treap[cur].ch[0]].si >= k) {
      y = cur;
      split(treap[cur].ch[0], k, x, treap[cur].ch[0]);
    } else {
      splitNew(cur, k - treap[treap[cur].ch[0]].si);
      x = cur;
      split(treap[cur].ch[1],
            k - treap[treap[cur].ch[0]].si - (treap[cur].r - treap[cur].l + 1),
            treap[cur].ch[1], y);
    }
    update(cur);
  }
}

signed main() {
  // freopen("C:/Users/qq260/OneDrive/WorkSpace/Code/Luogu/data/3960/1.in", "r",
          // stdin);
  scanf("%lld%lld%lld", &N, &M, &Q);
  f(i, 1, N) root[i] = newNode((i - 1) * M + 1, i * M - 1);
  f(i, 1, N) root[N + 1] = merge(root[N + 1], newNode(i * M, i * M));
  f(i, 1, Q) {
    reg a, b;
    scanf("%lld%lld", &a, &b);
    if (b != M) {
      reg r1, r2, r3;
      split(root[a], b, r1, r2);
      split(r1, b - 1, r1, r3);
      printf("%lld\n", treap[r3].l);
      reg r4, r5, r6;
      split(root[N + 1], a, r4, r5);
      split(r4, a - 1, r4, r6);
      root[a] = merge(r1, merge(r2, r6));
      root[N + 1] = merge(r4, merge(r5, r3));
    } else {
      reg r1, r2, r3;
      split(root[N + 1], a, r1, r2);
      split(r1, a - 1, r1, r3);
      printf("%lld\n", treap[r3].l);
      root[N + 1] = merge(r1, merge(r2, r3));
    }
  }
}