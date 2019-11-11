// luogu 1856
// POJ 1177
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#define SIZE 10006
#define MAX 20000
#define reg register
#define il inline
#define f(i, s, t) for (reg int i = s; i <= t; i++)
using namespace std;

struct Edge {
  int x, y, z, val;
  bool operator<(const Edge &that) const {
    return x < that.x || x == that.x && val > that.val;
  }
} ex[SIZE << 1], ey[SIZE << 1];

struct STNode {
  int l, r, cnt, num;
} st[SIZE << 2];

int N, ans, rx[SIZE], ry[SIZE], vx[MAX << 1], vy[MAX << 1];

void build(int p, int l, int r) {
  st[p].l = l, st[p].r = r;
  st[p].cnt = st[p].num = 0;
  if (l == r) return;
  int mid = (l + r) >> 1;
  build(p << 1, l, mid);
  build(p << 1 | 1, mid + 1, r);
}
void modify(int k, int p, int l, int r, int d) {
  if (l <= st[p].l && st[p].r <= r) st[p].cnt += d;
  if (st[p].l == st[p].r) {
    st[p].cnt += d;
    if (st[p].cnt)
      st[p].num =
          k ? (ry[st[p].r + 1] - ry[st[p].l]) : (rx[st[p].r + 1] - rx[st[p].l]);
    else
      st[p].num = 0;
    return;
  }
  int mid = (st[p].l + st[p].r) >> 1;
  if (l <= mid) modify(k, p << 1, l, r, d);
  if (mid < r) modify(k, p << 1 | 1, l, r, d);
  st[p].num = st[p].cnt ? (k ? (ry[st[p].r + 1] - ry[st[p].l])
                             : (rx[st[p].r + 1] - rx[st[p].l]))
                        : (st[p << 1].num + st[p << 1 | 1].num);
}
int ask(int p, int l, int r) {
  if (l <= st[p].l && st[p].r <= r) return st[p].num;
  int mid = (st[p].l + st[p].r) >> 1, ans = 0;
  if (l <= mid) ans += ask(p << 1, l, r);
  if (mid < r) ans += ask(p << 1 | 1, l, r);
  return ans;
}

int main() {
  scanf("%d", &N);
  f(i, 1, N) {
    reg int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    ex[i] = (Edge){y1, x1, x2, 1};
    ex[i + N] = (Edge){y2, x1, x2, -1};
    ey[i] = (Edge){x1, y1, y2, 1};
    ey[i + N] = (Edge){x2, y1, y2, -1};
    rx[i] = x1, rx[i + N] = x2;
    ry[i] = y1, ry[i + N] = y2;
  }
  N <<= 1;
  sort(ex + 1, ex + 1 + N);
  sort(ey + 1, ey + 1 + N);
  sort(rx + 1, rx + N + 1);
  int t = unique(rx + 1, rx + N + 1) - (rx + 1);
  f(i, 1, t) vx[rx[i] + MAX] = lower_bound(rx + 1, rx + t + 1, rx[i]) - rx;
  build(1, 1, t);
  f(i, 1, N) {
    int tmp = ask(1, vx[ex[i].y + MAX], vx[ex[i].z + MAX] - 1);
    modify(0, 1, vx[ex[i].y + MAX], vx[ex[i].z + MAX] - 1, ex[i].val);
    tmp -= ask(1, vx[ex[i].y + MAX], vx[ex[i].z + MAX] - 1);
    ans += abs(tmp);
  }
  sort(ry + 1, ry + N + 1);
  t = unique(ry + 1, ry + N + 1) - (ry + 1);
  f(i, 1, t) vy[ry[i] + MAX] = lower_bound(ry + 1, ry + t + 1, ry[i]) - ry;
  build(1, 1, t);
  f(i, 1, N) {
    int tmp = ask(1, vy[ey[i].y + MAX], vy[ey[i].z + MAX] - 1);
    modify(1, 1, vy[ey[i].y + MAX], vy[ey[i].z + MAX] - 1, ey[i].val);
    tmp -= ask(1, vy[ey[i].y + MAX], vy[ey[i].z + MAX] - 1);
    ans += abs(tmp);
  }
  printf("%d\n", ans);
}