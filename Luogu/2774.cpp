#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 106, INF = (1 << 31) - 1;
int N, M, S, T, dep[SN * SN],  //
    tot, Head[SN * SN], Ver[SN * SN * 3], Next[SN * SN * 3], Edge[SN * SN * 3];

il void add(int x, int y, int z) {
  // printf("%d %d %d\n", x, y, z);
  Ver[++tot] = y, Next[tot] = Head[x], Edge[tot] = z, Head[x] = tot;
  Ver[++tot] = x, Next[tot] = Head[y], Edge[tot] = 0, Head[y] = tot;
}

il bool bfs() {
  ms(dep, 0);
  dep[S] = 1;
  queue<int> q;
  q.push(S);
  while (q.size()) {
    reg x = q.front();
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]) {
      reg y = Ver[i], z = Edge[i];
      if (!z || dep[y]) continue;
      dep[y] = dep[x] + 1;
      if (y == T) return 1;
      q.push(y);
    }
  }
  return 0;
}

int dinic(int x, int flow) {
  if (x == T) return flow;
  reg res = flow;
  for (reg i = Head[x]; i && res; i = Next[i])
    if (Edge[i] && dep[x] + 1 == dep[Ver[i]]) {
      reg k = dinic(Ver[i], min(res, Edge[i]));
      if (!k) dep[Ver[i]] = 0;
      Edge[i] -= k, Edge[i ^ 1] += k;
      res -= k;
    }
  return flow - res;
}

int main() {
  scanf("%d%d", &N, &M);
  S = N * M + 1, T = N * M + 2;
  tot = 1;
  f(i, 1, N) f(j, 1, M) {
    reg p = (i - 1) * M + j;
    if ((i + j) % 2) continue;
    if (p + M <= N * M) add(p, p + M, INF);
    if (0 < p - M) add(p, p - M, INF);
    if (p + 1 <= i * M) add(p, p + 1, INF);
    if ((i - 1) * M < p - 1) add(p, p - 1, INF);
  }
  reg cnt = 0;
  f(i, 1, N) f(j, 1, M) {
    reg a, p = (i - 1) * M + j;
    scanf("%d", &a);
    if ((i + j) % 2)
      add(p, T, a);
    else
      add(S, p, a);
    cnt += a;
  }
  reg maxflow = 0, flow = 0;
  while (bfs())
    while (flow = dinic(S, INF)) maxflow += flow;
  printf("%d\n", cnt - maxflow);
}