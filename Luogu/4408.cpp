#include <bits/stdc++.h>
using namespace std;
#define reg register
#define f(i, s, t) for (reg int i = s; i != t + 1; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))
typedef long long ll;

const int SN = 200006;
int N, M, p, q, tot, Head[SN], Ver[SN << 1], Next[SN << 1];
ll Edge[SN << 1], d[2][SN];

il void add(int x, int y, int z) {
  Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
}

void dfs(int x, int tfa, int& a, int k) {
  for (reg int i = Head[x]; i; i = Next[i]) {
    if (Ver[i] == tfa) continue;
    d[k][Ver[i]] = d[k][x] + Edge[i];
    if (d[k][a] < d[k][Ver[i]]) a = Ver[i];
    dfs(Ver[i], x, a, k);
  }
}

int main() {
  scanf("%d%d", &N, &M);
  f(i, 1, M) {
    reg int u, v, t;
    scanf("%d%d%d", &u, &v, &t);
    add(u, v, t), add(v, u, t);
  }
  reg int p = 0, q = 0;
  dfs(1, 0, p, 0);
  ms(d, 0);
  dfs(p, 0, q, 0);
  dfs(q, 0, p, 1);
  reg ll cnt = 0;
  f(i, 1, N) if (i ^ q && i ^ p) cnt = max(cnt, min(d[0][i], d[1][i]));
  printf("%lld\n", cnt + d[0][q]);
}