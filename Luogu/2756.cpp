#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 126, INF = (1 << 31) - 1;
int N, M, S, T, d[SN],  //
    tot, Head[SN], Next[SN * SN << 1], Ver[SN * SN << 1], Edge[SN * SN << 1];

il int read() {
  reg x = 0, f = 1;
  register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    if (ch == '-') f = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x * f;
}

il void add(int x, int y, int z) {
  Ver[++tot] = y, Next[tot] = Head[x], Edge[tot] = z, Head[x] = tot;
  Ver[++tot] = x, Next[tot] = Head[y], Edge[tot] = 0, Head[y] = tot;
}

il bool bfs() {
  queue<int> q;
  q.push(S);
  ms(d, 0), d[S] = 1;
  while (q.size()) {
    reg x = q.front();
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]) {
      reg y = Ver[i];
      if (d[y] || Edge[i] == 0) continue;
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
  for (reg i = Head[x]; i && res; i = Next[i]) {
    reg y = Ver[i];
    if (d[y] != d[x] + 1 || Edge[i] == 0) continue;
    reg k = dinic(y, min(res, Edge[i]));
    if (k == 0) d[y] = 0;
    Edge[i] -= k, Edge[i ^ 1] += k, res -= k;
  }
  return flow - res;
}

int main() {
  // freopen("./data/2756/5.in", "r", stdin);
  M = read(), N = read();
  S = N + 1, T = N + 2, tot = 1;
  f(i, 1, M) add(S, i, 1);
  f(j, M + 1, N) add(j, T, 1);
  for (reg i = read(), j = read(); i != -1; i = read(), j = read())
    add(i, j, 1);
  reg maxflow = 0, flow;
  while (bfs())
    while (flow = dinic(S, INF)) maxflow += flow;
  if (maxflow == 0) return puts("No Solution!"), 0;
  printf("%d\n", maxflow);
  f(x, M + 1, N) {
    for (reg i = Head[x]; i; i = Next[i]) {
      if (Ver[i] == T || Edge[i] == 0) continue;
      printf("%d %d\n", Ver[i], x);
      break;
    }
  }
}