#include <cstdio>
#include <iostream>
#define il inline
#define SIZE 400006
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
using namespace std;

struct Node {
  int l, r;
} INITION, fstn[SIZE << 5];
int root[SIZE], si[SIZE << 5], f[SIZE << 5], N, M, tot;

int build(int l, int r) {
  reg int p = ++tot;
  fstn[p].l = fstn[p].r = 0;
  if (l == r) {
    f[p] = l;
    si[p] = 1;
    return p;
  }
  reg int mid = (l + r) >> 1, tl = build(l, mid), tr = build(mid + 1, r);
  fstn[p].l = tl, fstn[p].r = tr;
  return p;
}

int modify(int p, int l, int r, int x, int y) {
  reg int q = ++tot;
  fstn[q] = fstn[p];
  if (l == r) {
    f[q] = y;
    return q;
  }
  reg int mid = (l + r) >> 1;
  if (x <= mid) fstn[q].l = modify(fstn[p].l, l, mid, x, y);
  if (mid < x) fstn[q].r = modify(fstn[p].r, mid + 1, r, x, y);
  return q;
}
int ask(int p, int l, int r, int x) {
  if (l == r) return p;
  int mid = (l + r) >> 1;
  if (x <= mid) return ask(fstn[p].l, l, mid, x);
  if (mid < r) return ask(fstn[p].r, mid + 1, r, x);
}

int getfa(int ver, int x) {
  reg int p = ask(root[ver], 1, N, x);
  if (f[p] == x)
    return p;
  else
    return getfa(ver, f[p]);
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  scanf("%d%d", &N, &M);
  tot = 0;
  root[0] = build(1, N);
  f(i, 1, M) {
    reg int opr, a, b;
    scanf("%d", &opr);
    if (opr == 1) {
      root[i] = root[i - 1];
      scanf("%d%d", &a, &b);
      reg int fa = getfa(i - 1, a), fb = getfa(i - 1, b);
      if (f[fa] == f[fb]) continue;
      if (si[fa] > si[fb]) swap(fa, fb);
      root[i] = modify(root[i - 1], 1, N, f[fa], f[fb]);
      si[fb] += si[fa];
    }
    if (opr == 2) scanf("%d", &a), root[i] = root[a];
    if (opr == 3) {
      root[i] = root[i - 1], scanf("%d%d", &a, &b),
      getfa(i, a) == getfa(i, b) ? puts("1") : puts("0");
    }
  }
}