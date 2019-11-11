#pragma GCC optimize(3, "Ofast", "inline")
// Ch 4701
// ykhoj 3357
// luogu 4169
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define SIZE 1000006
#define reg register
#define il inline
#define f(a, b, c) for (reg int a = b; a <= c; a++)
#define INF 0x3f3f3f3f
#define ciR const int &
using namespace std;

struct PointNode {
  int t, x, y;
  bool operator<(const PointNode &that) const {
    return x < that.x || x == that.x && y < that.y;
  }
} a[SIZE], b[SIZE];

int N, M, maxy = 0, c[SIZE], ans[SIZE];

il int max(ciR a, ciR b) { return a > b ? a : b; };
il int min(ciR a, ciR b) { return a < b ? a : b; };
il int abs(int a) { return a < 0 ? -a : a; };

il void add(int x, ciR y) {
  for (; x < maxy; x += x & -x) c[x] = max(c[x], y);
}

il int ask(int x) {
  int ans = -INF;
  for (; x; x -= x & -x) ans = max(ans, c[x]);
  return ans;
}

il void re(int x) {
  for (; x < maxy; x += x & -x) c[x] = -INF;
}

il void work(ciR st, ciR ed, ciR delta, ciR dx, ciR dy) {
  // cout << st << ' ' << ed << ' ' << delta << ' ' << dx << ' ' << dy << endl;
  for (reg int i = st; i != ed; i += delta) {
    int y = (dy == 1) ? b[i].y : maxy - b[i].y, num = dx * b[i].x + dy * b[i].y;
    if (a[b[i].t].t == 1) add(y, num);
    if (a[b[i].t].t == 2) ans[b[i].t] = min(ans[b[i].t], abs(num - ask(y)));
  }
  for (reg int i = st; i != ed; i += delta) {
    // cout << '?' << i << endl;
    if (a[b[i].t].t == 1) re((dy == 1) ? b[i].y : maxy - b[i].y);
  }
}

void cdq(ciR l, ciR r) {
  // cout << l << ' ' << r << endl;
  int mid = (l + r) >> 1;
  if (l < mid) cdq(l, mid);
  if (mid + 1 < r) cdq(mid + 1, r);
  int tot = 0;
  f(i, l, r) if (i <= mid && a[i].t == 1 || i > mid && a[i].t == 2) {
    b[++tot] = a[i];
    b[tot].t = i;
  }
  sort(b + 1, b + 1 + tot);
  work(1, tot + 1, 1, 1, 1);
  work(1, tot + 1, 1, 1, -1);
  work(tot, 0, -1, -1, 1);
  work(tot, 0, -1, -1, -1);
}

il int read() {
  reg int x = 0;
  reg char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

int main() {
  N = read(), M = read();
  f(i, 1, N) {
    a[i].x = read() + 1, a[i].y = read() + 1;
    a[i].t = 1;
    maxy = max(maxy, a[i].y);
  }
  f(i, 1, M) {
    a[i + N].t = read(), a[i + N].x = read() + 1, a[i + N].y = read() + 1;
    maxy = max(maxy, a[i + N].y);
  }
  ++maxy;
  memset(ans, 0x3f, sizeof(ans));
  memset(c, 0xcf, sizeof(c));
  cdq(1, N + M);
  f(i, 1, M + N) if (a[i].t == 2) printf("%d\n", ans[i]);
}