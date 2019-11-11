#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 456, SM = 45006, INF = 0x7fffffff;
int N, M, S, T, d[SN],  //
    tot, Head[SN], Next[SM << 1], Ver[SM << 1], Edge[SM << 1];

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x; 
}

il void add(int x, int y, int z) {
  Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
  Ver[++tot] = x, Edge[tot] = 0, Next[tot] = Head[y], Head[y] = tot;
}

il bool bfs() {
  queue<int> q;
  ms(d, 0);
  d[S] = 1, q.push(S);
  while (q.size()) {
    reg x = q.front();
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]) {
      reg y = Ver[i];
      if (d[y] || Edge[i] == 0) continue;
      d[y] = d[x] + 1;
      if (y == T) return 1;
      q.push(y);
    }
  }
  return 0;
}

int dinic(int x, int flow) {
  if (x == T) return flow;
  reg res = flow;
  for (reg i = Head[x]; i && res; i = Next[i]) {
    reg y = Ver[i];
    if (d[y] != d[x] + 1 || Edge[i] == 0) continue;
    reg k = dinic(y, min(res, Edge[i]));
    if (k == 0) d[y] = 0;
    Edge[i] -= k, Edge[i ^ 1] += k;
    res -= k;
  }
  return flow - res;
}

// extern int dinic(int , int);

int main() {
  M = read(), N = read();
  S = N + M + 1, T = N + M + 2, tot = 1;
  reg sum = 0;
  f(i, 1, M) {
    reg x = read();
    sum += x;
    add(i + N, T, x);
  }
  f(i, 1, N) add(S, i, read());
  f(i, 1, N) f(j, 1, M) add(i, j + N, 1);
  reg maxflow = 0, flow;
  while (bfs())
    while (flow = dinic(S, INF)) maxflow += flow;
  // printf("%d %d\n", sum, maxflow);
  if (maxflow != sum) return puts("0"), 0;
  puts("1");
  f(x, 1 + N, M + N) {
    for (reg i = Head[x]; i; i = Next[i])
      if (Ver[i] != T && Edge[i] == 1) printf("%d ", Ver[i]);
    puts("");
  }
}