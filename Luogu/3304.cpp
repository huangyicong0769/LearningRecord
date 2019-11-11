#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline
#define mp(a, b) make_pair(a, b)
typedef long long ll;

const int SN = 400006;
int N, tot, ans, Head[SN], Next[SN], Ver[SN], fa[SN];
ll dp[SN], Edge[SN], f[SN];

il void add(int x, int y, ll z) {
  Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
}

void dfs(int x, int tfa, ll tdp) {
  dp[x] = tdp;
  fa[x] = tfa;
  f[x] = 0;
  for (reg i = Head[x]; i; i = Next[i]) {
    if (Ver[i] == tfa) continue;
    dfs(Ver[i], x, tdp + Edge[i]);
    f[x] = max(f[x], f[Ver[i]] + Edge[i]);
  }
}

il void RLP(int x, int tfa, ll tdp) {
  dfs(x, tfa, tdp);
  while (1) {
    reg y = 0, cnt = 0;
    for (reg i = Head[x]; i; i = Next[i])
      if (Ver[i] != tfa && f[x] == f[Ver[i]] + Edge[i]) y = Ver[i], cnt++;
    if (cnt != 1) break;
    tfa = x, x = y, ans++;
  }
}

int main() {
  scanf("%d", &N);
  if (N == 2) {
    puts("2");
    return 0;
  }
  f(i, 2, N) {
    reg a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    add(a, b, c), add(b, a, c);
  }
  dfs(1, 0, 0);
  reg p = 0;
  f(i, 1, N) if (dp[i] > dp[p]) p = i;
  dfs(p, 0, 0);
  p = 0;
  f(i, 1, N) if (dp[i] > dp[p]) p = i;
  register ll L = dp[p];
  while (dp[fa[p]] * 2 >= L) p = fa[p];
  if (dp[p] * 2 == L) {
    dfs(p, 0, 0);
    priority_queue<pair<ll, int> > pq;
    for (reg i = Head[p]; i; i = Next[i])
      pq.push(mp(-f[Ver[i]] + Edge[i], Ver[i]));
    reg a = pq.top().second;
    register ll av = -pq.top().first;
    pq.pop();
    reg b = pq.top().second;
    register ll bv = -pq.top().first;
    pq.pop();
    if (pq.empty()) {
      ans += 2;
      RLP(a, p, 0), RLP(b, p, 0);
    } else if (bv > -pq.top().first) {
      ans += 2;
      RLP(a, p, 0), RLP(b, p, 0);
    } else if (av > bv) {
      ans++;
      RLP(a, p, 0);
    }
  } else {
    ans++;
    RLP(p, fa[p], 0);
    RLP(fa[p], p, 0);
  }
  printf("%lld\n%d\n", L, ans);
}