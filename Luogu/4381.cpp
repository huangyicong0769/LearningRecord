#include <cstdio>
#include <iostream>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

typedef long long ll;
const int SIZE = 1000006;
int N, tot, t, Head[SIZE << 1], Next[SIZE << 1], Edge[SIZE << 1],
    Leng[SIZE << 1], q[SIZE << 1], c[SIZE], du[SIZE];
ll f[SIZE], d[SIZE], a[SIZE << 1], s[SIZE << 1];
bool b[SIZE];

il void add(const reg &x, const reg &y, const reg &z) {
  Edge[++tot] = y, Leng[tot] = z, Next[tot] = Head[x], Head[x] = tot, du[y]++;
}

il void bfs(int s, int t) {
  c[q[1] = s] = t;
  for (reg l = 1, r = 1; l <= r; l++)
    for (reg i = Head[q[l]]; i; i = Next[i])
      if (!c[Edge[i]]) c[q[++r] = Edge[i]] = t;
}

il void topsort() {
  reg l = 1, r = 0;
  f(i, 1, N) if (du[i] == 1) q[++r] = i;
  for (; l <= r; l++)
    for (reg i = Head[q[l]]; i; i = Next[i])
      if (du[Edge[i]] > 1) {
        d[c[q[l]]] = max(d[c[q[l]]], f[q[l]] + Leng[i] + f[Edge[i]]);
        f[Edge[i]] = max(f[Edge[i]], f[q[l]] + Leng[i]);
        if (--du[Edge[i]] == 1) q[++r] = Edge[i];
      }
}

il void dp(int t, int x) {
  reg y = x, m = 0, z = 0, i;
  do {
    a[++m] = f[y];
    du[y] = 1;
    for (i = Head[y]; i; i = Next[i])
      if (du[Edge[i]] > 1) {
        s[m + 1] = s[m] + Leng[i];
        y = Edge[i];
        break;
      }
  } while (i);
  if (m == 2) {
    for (reg i = Head[y]; i; i = Next[i])
      if (Edge[i] == x) z = max(z, Leng[i]);
    d[t] = max(d[t], f[x] + f[y] + z);
    return;
  }
  for (reg i = Head[y]; i; i = Next[i])
    if (Edge[i] == x) {
      s[m + 1] = s[m] + Leng[i];
      break;
    }
  f(i, 1, m - 1) {
    a[m + i] = a[i];
    s[m + i] = s[m + 1] + s[i];
  }
  reg l = 1, r = 1;
  q[1] = 1;
  f(i, 2, (m << 1) - 1) {
    while (l <= r && i - q[l] >= m) l++;
    d[t] = max(d[t], a[i] + a[q[l]] + s[i] - s[q[l]]);
    while (l <= r && a[q[r]] - s[q[r]] <= a[i] - s[i]) r--;
    q[++r] = i;
  }
}

int main() {
  scanf("%d", &N);
  f(i, 1, N) {
    reg a, b;
    scanf("%d%d", &a, &b);
    add(i, a, b);
    add(a, i, b);
  }
  f(i, 1, N) if (!c[i]) bfs(i, ++t);
  topsort();
  ll ans = 0;
  f(i, 1, N) if (du[i] > 1 && !b[c[i]]) {
    b[c[i]] = 1;
    dp(c[i], i);
    ans += d[c[i]];
  }
  printf("%lld\n", ans);
}