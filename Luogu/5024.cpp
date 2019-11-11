#include <cstdio>
#include <iostream>
using namespace std;
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)

typedef long long ll;
const ll SN = 100006, INF = (1LL << 60) - 1;
int N, M, f[SN][17], dep[SN];
int tot, Head[SN], Ver[SN << 1], Next[SN << 1];
ll g[SN][17][2][2], dp[SN][2];

il void add(int u, int v) {
  Ver[++tot] = v, Next[tot] = Head[u], Head[u] = tot;
}
void dfs1(int x, int fa) {
  dep[x] = dep[fa] + 1;
  f[x][0] = fa;
  g[x][0][0][0] = INF;
  f(i, 1, 16) f[x][i] = f[f[x][i - 1]][i - 1];
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == fa) continue;
    dfs1(y, x);
    dp[x][0] += dp[y][1];
    dp[x][1] += min(dp[y][0], dp[y][1]);
  }
}
void dfs2(int x) {
  g[x][0][1][0] = dp[f[x][0]][0] - dp[x][1];
  g[x][0][0][1] = g[x][0][1][1] = dp[f[x][0]][1] - min(dp[x][0], dp[x][1]);
  f(i, 1, 16) {
    g[x][i][0][0] = min(g[x][i - 1][0][0] + g[f[x][i - 1]][i - 1][0][0],
                        g[x][i - 1][0][1] + g[f[x][i - 1]][i - 1][1][0]);
    g[x][i][0][1] = min(g[x][i - 1][0][0] + g[f[x][i - 1]][i - 1][0][1],
                        g[x][i - 1][0][1] + g[f[x][i - 1]][i - 1][1][1]);
    g[x][i][1][0] = min(g[x][i - 1][1][0] + g[f[x][i - 1]][i - 1][0][0],
                        g[x][i - 1][1][1] + g[f[x][i - 1]][i - 1][1][0]);
    g[x][i][1][1] = min(g[x][i - 1][1][0] + g[f[x][i - 1]][i - 1][0][1],
                        g[x][i - 1][1][1] + g[f[x][i - 1]][i - 1][1][1]);
  }
  for (reg i = Head[x]; i; i = Next[i])
    if (Ver[i] != f[x][0]) dfs2(Ver[i]);
}
il void preWork() {
  dfs1(1, 0);
  dfs2(1);
}
il ll query(int u, int s1, int v, int s2) {
  if (dep[v] > dep[u]) swap(u, v), swap(s1, s2);
  // printf("0 %d %d\n", u, v);
  register ll u0 = INF, u1 = INF, v0 = INF, v1 = INF, L, l0 = INF, l1 = INF;
  s1 ? u1 = dp[u][1] : u0 = dp[u][0];
  s2 ? v1 = dp[v][1] : v0 = dp[v][0];
  for (reg i = 16; i >= 0; i--)
    if (dep[f[u][i]] >= dep[v]) {
      register ll t0 = u0, t1 = u1;
      u0 = min(t0 + g[u][i][0][0], t1 + g[u][i][1][0]);
      u1 = min(t0 + g[u][i][0][1], t1 + g[u][i][1][1]);
      u = f[u][i];
    }
  // printf("1 %d %d\n", u, v);
  if (u == v)
    L = u, s2 ? l1 = u1 : l0 = u0;
  else {
    for (reg i = 16; i >= 0; i--)
      if (f[u][i] != f[v][i]) {
        register ll t0 = u0, t1 = u1, r0 = v0, r1 = v1;
        u0 = min(t0 + g[u][i][0][0], t1 + g[u][i][1][0]);
        u1 = min(t0 + g[u][i][0][1], t1 + g[u][i][1][1]);
        v0 = min(r0 + g[v][i][0][0], r1 + g[v][i][1][0]);
        v1 = min(r0 + g[v][i][0][1], r1 + g[v][i][1][1]);
        u = f[u][i], v = f[v][i];
      }
    L = f[u][0];
    l0 = dp[L][0] - dp[u][1] - dp[v][1] + u1 + v1;
    l1 = dp[L][1] - min(dp[u][0], dp[u][1]) - min(dp[v][0], dp[v][1]) +
         min(u0, u1) + min(v0, v1);
  }
  // printf("2 %d\n", L);
  register ll ans;
  if (L == 1)
    ans = min(l0, l1);
  else {
    for (reg i = 16; i >= 0; i--)
      if (dep[f[L][i]] > dep[1]) {
        register ll t0 = l0, t1 = l1;
        l0 = min(t0 + g[L][i][0][0], t1 + g[L][i][1][0]);
        l1 = min(t0 + g[L][i][0][1], t1 + g[L][i][1][1]);
        L = f[L][i];
      }
    ans = min(dp[1][0] - dp[L][1] + l1,
              dp[1][1] - min(dp[L][0], dp[L][1]) + min(l0, l1));
  }
  return ans < INF ? ans : -1;
}

int main() {
  // freopen("input.txt", "r", stdin);
  char ts[2];
  scanf("%d%d%s", &N, &M, ts);
  f(i, 1, N) scanf("%lld", &dp[i][1]);
  f(i, 2, N) {
    reg u, v;
    scanf("%d%d", &u, &v);
    add(u, v), add(v, u);
  }
  preWork();
  f(i, 1, M) {
    reg u, v, s1, s2;
    scanf("%d%d%d%d", &u, &s1, &v, &s2);
    printf("%lld\n", query(u, s1, v, s2));
  }
}