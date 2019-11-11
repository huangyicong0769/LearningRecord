#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 1e4 + 6, SM = 2e5 + 6, INF = 0x7fffffff;
int N, S = 1e4 + 1, T = 1e4 + 2, d[SN],   //
    tot, H1[SN], V1[SM], N1[SM], E1[SM],  //
    H2[60], N2[SN];
bool vis[SN];

il int read() {
  reg x = 0; char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il void add(int x, int y, int z) {
  V1[++tot] = y, E1[tot] = z, N1[tot] = H1[x], H1[x] = tot;
  V1[++tot] = x, E1[tot] = 0, N1[tot] = H1[y], H1[y] = tot;
}

il bool bfs() {
  queue<int> q;
  ms(d, 0);
  d[S] = 1, q.push(S);
  while (q.size()) {
    reg x = q.front();
    q.pop();
    for (reg i = H1[x]; i; i = N1[i]) {
      reg y = V1[i], z = E1[i];
      if (d[y] || z == 0) continue;
      d[y] = d[x] + 1;
      if (y == T) return true;
      q.push(y);
    }
  }
  return false;
}

int dinic(int x, int flow) {
  if (x == T) return flow;
  reg res = flow;
  for (reg i = H1[x]; i; i = N1[i]) {
    reg y = V1[i];
    if (d[y] != d[x] + 1 || E1[i] == 0) continue;
    reg k = dinic(y, min(res, E1[i]));
    if (k == 0)
      d[y] = 0;
    else {
      E1[i] -= k, E1[i ^ 1] += k;
      N2[x >> 1] = y >> 1;
      res += k;
    }
  }
  return flow - res;
}

int main() {
  N = read(), tot = 1;
  reg num = 0, ans = 0;
  while (num <= N) {
    ans++;
    add(S, ans << 1, 1), add(ans << 1 | 1, T, 1);
    for (reg i = sqrt(ans) + 1; i * i < ans * 2; i++)
      add(i * i - ans << 1, ans << 1 | 1, 1);
    reg maxFlow = 0, flow;
    while (bfs())
      while (flow = dinic(S, INF)) maxFlow += flow;
    if (maxFlow == 0) H2[++num] = ans;
  }
  printf("%d\n", ans - 1);
  f(x, 1, N) if (!vis[H2[x]]) {
    for (reg i = H2[x]; i && i != (T >> 1); i = N2[i]) {
      vis[i] = 1;
      printf("%d ", i);
    }
    puts("");
  }
}