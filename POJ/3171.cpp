#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define SIZE 100006
#define reg register
#define f(i, s, t) for (reg int i = s; i != t; i++)
using namespace std;

const int INF = 0x3f3f3f3f;

struct Node {
  int l, r, d;
  bool operator<(const Node& that) const { return r < that.r; }
} a[SIZE * 4], b[SIZE];

int N, M, E, f[SIZE];

void build(int p, int l, int r) {
  a[p].l = l, a[p].r = r;
  if (l == r) {
    a[p].d = f[l];
    return;
  }
  reg int mid = (l + r) >> 1;
  build(p << 1, l, mid);
  build(p << 1 | 1, mid + 1, r);
  a[p].d = min(a[p << 1].d, a[p << 1 | 1].d);
}
int ask(int p, int l, int r) {
  // printf("a:%d %d %d %d %d\n", p, a[p].l, a[p].r, l, r);
  if (l <= a[p].l && a[p].r <= r) return a[p].d;
  reg int mid = (a[p].l + a[p].r) >> 1, ans = INF;
  if (l <= mid) ans = min(ans, ask(p << 1, l, r));
  if (mid < r) ans = min(ans, ask(p << 1 | 1, l, r));
  return ans;
}
void modify(int p, int x, int y) {
  // printf("m:%d %d %d %d %d\n", p, a[p].l, a[p].r, x, y);
  if (a[p].l == a[p].r) {
    a[p].d = y;
    return;
  }
  reg int mid = (a[p].l + a[p].r) >> 1;
  if (x <= mid)
    modify(p << 1, x, y);
  else
    modify(p << 1 | 1, x, y);
  a[p].d = min(a[p << 1].d, a[p << 1 | 1].d);
}

int main() {
  memset(f, 0x3f, sizeof(f));
  scanf("%d%d%d", &N, &M, &E);
  f(i, 0, N) scanf("%d%d%d", &b[i].l, &b[i].r, &b[i].d);
  sort(b, b + N);
  f[M] = 0;
  build(1, M, E);
  reg int ans = INF;
  f(i, 0, N) {
    f[b[i].r] = min(f[b[i].r], ask(1, b[i].l - 1, b[i].r) + b[i].d);
    modify(1, b[i].r, f[b[i].r]);
    if (b[i].r >= E) ans = min(ans, f[b[i].r]);
    // printf("%d %d %d\n", i, ask(1, b[i].r, b[i].r), f[b[i].r]);
  }
  printf("%d\n", ans);
}
