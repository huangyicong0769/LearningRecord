#include <cstdio>
#include <iostream>
#define il inline
#define reg register int
#define ll long long
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SI = 100006;
int N, M, tot, Head[SI << 1], Ver[SI * 5 << 1], Next[SI * 5 << 1], dfn[SI],
    low[SI], si[SI];
ll ans[SI];
bool cut[SI];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void tarjan(const int &x) {
  dfn[x] = low[x] = ++tot, si[x] = 1;
  reg sum = 0, cnt = 0;
  for (reg i = Head[x]; i; i = Next[i]) {
    const int &y = Ver[i];
    if (!dfn[y]) {
      tarjan(y);
      si[x] += si[y];
      low[x] = min(low[x], low[y]);
      if (low[y] >= dfn[x]) {
        cnt++;
        ans[x] += (ll)si[y] * (N - si[y]);
        sum += si[y];
        if (x != 1 || cnt > 1) cut[x] = 1;
      }
    } else low[x] = min(low[x], dfn[y]);
  }
  if (cut[x]) ans[x] += (ll)(N - sum - 1) * (sum + 1) + N - 1;
  else ans[x] = 2 * (N - 1);
}

int main() {
  scanf("%d%d", &N, &M);
  f(i, 1, M) {
    reg x, y;
    scanf("%d%d", &x, &y);
    if (x == y) continue;
    add(x, y), add(y, x);
  }
  tot = 0;
  tarjan(1);
  f(i, 1, N) printf("%lld\n", ans[i]);
}