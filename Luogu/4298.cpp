#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 206;
int N, M, tot, ct[SN][SN], f[SN], vis[SN];
bool l[SN], r[SN], ban[SN], to[SN];

int dfs(const int &x, const int &tsp) {
  if (ban[x]) return 0;
  f(i, 1, N) {
    if (!ct[x][i] || vis[i] == tsp || ban[i]) continue;
    vis[i] = tsp;
    if (!f[i] || dfs(f[i], tsp)) {
      to[x] = 1, f[i] = x;
      return 1;
    }
  }
  return 0;
}
void fakeDfs(const int &x) {
  if (r[x]) return;
  r[x] = 1;
  f(i, 1, N) if (ct[x][i] && !l[i]) l[i] = 1, fakeDfs(f[i]);
}

int main() {
  scanf("%d%d", &N, &M);
  f(i, 1, M) {
    reg u, v;
    scanf("%d%d", &u, &v);
    ct[u][v] = 1;
  }
  f(i, 1, N) ct[i][i] = 1;
  f(k, 1, N) f(i, 1, N) f(j, 1, N) ct[i][j] |= ct[i][k] & ct[k][j];
  f(i, 1, N) ct[i][i] = 0;
  reg ans = N;
  f(i, 1, N) ans -= dfs(i, i);
  printf("%d\n", ans);
  f(i, 1, N) if (!to[i]) fakeDfs(i);
  f(i, 1, N) printf("%d", !l[i] && r[i]);
  puts("");
  f(k, 1, N) {
    ms(vis, 0);
    ms(ban, 0);
    ms(f, 0);
    reg tmp = 0;
    f(i, 1, N) if (ct[i][k] || ct[k][i] || i == k) ban[i] = 1;
    else tmp++;
    f(i, 1, N) tmp -= dfs(i, i);
    printf("%d", tmp == ans - 1);
  }
  puts("");
}