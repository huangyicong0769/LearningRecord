// ykhoj P3358
// POJ 2104
// SPOJ 3946
// luohu SP3946
#include <cstdio>
#include <iostream>
#define reg register
#define il inline
#define f(a, b, c) for (reg int a = b; a <= c; a++)
#define SIZE 100006
#define INF 10e9
using namespace std;

struct Node {
  int op, x, y, z;
} q[SIZE << 1], rq[SIZE << 1], lq[SIZE << 1];

int M, N, t, ans[SIZE], c[SIZE];

il int ask(int x) {
  int ans = 0;
  for (; x; x -= x & -x) ans += c[x];
  return ans;
}

il void add(int x, int y) {
  for (; x <= N; x += x & -x) c[x] += y;
}

void solve(int l, int r, int s, int t) {
  // cout << l << ' ' << r << ' ' << s << ' ' << t << endl;
  if (s > t) return;
  if (l == r) {
    f(i, s, t) if (q[i].op > 0) ans[q[i].op] = l;
    return;
  }
  int mid = (l + r) >> 1, lt = 0, rt = 0;
  f(i, s, t) {
    if (q[i].op > 0) {
      int cnt = ask(q[i].y) - ask(q[i].x - 1);
      if (q[i].z <= cnt)
        lq[++lt] = q[i];
      else
        q[i].z -= cnt, rq[++rt] = q[i];
    } else {
      if (q[i].y <= mid)
        add(q[i].x, 1), lq[++lt] = q[i];
      else
        rq[++rt] = q[i];
    }
  }
  f(i, s, t) if (q[i].op==0 && q[i].y <= mid) add(q[i].x, -1);
  f(i, 1, lt) q[s + i - 1] = lq[i];
  f(i, 1, rt) q[s + lt + i - 1] = rq[i];
  solve(l, mid, s, s + lt - 1);
  solve(mid + 1, r, s + lt, t);
}

int main() {
  scanf("%d%d", &N, &M);
  t = 0;
  f(i, 1, N) {
    ++t;
    scanf("%d", &q[t].y);
    q[t].op = 0, q[t].x = i;
  }
  f(i, 1, M) {
    ++t;
    scanf("%d%d%d", &q[t].x, &q[t].y, &q[t].z);
    q[t].op = i;
  }
  solve(-INF, INF, 1, t);
  f(i, 1, M) printf("%d\n", ans[i]);
}