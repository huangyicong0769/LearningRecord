#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a));

const int SN = 1056, SM = 20056, INF = 0x7fffffff;
int N, K, S, T, d[SN],  //
    tot, Head[SN], Ver[SM << 1], Next[SM << 1], Edge[SM << 1];

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
  d[S] = 0, q.push(S);
  while (q.size()){
    reg x = q.front();
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]){
      reg y = Ver[i];
      if (d[y] || !Edge[i]) continue;
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
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (d[y] != d[x] + 1 || !Edge[i]) continue;
    reg k = dinic(y, min(res, Edge[i]));
    if (!k) d[y] = 0;
    Edge[i] -= k, Edge[i ^ 1] += k;
    res -= k;
  }
  return flow - res;
}

int main(int argc, const char** argv) {
  K = read(), N = read();
  S = K + N + 1, T = S + 1, tot = 1;
  f(i, 1, N) add(S, i, 1);
  reg sum = 0;
  f(i, 1, K) {
    reg x = read();
    sum += x;
    add(i + N, T, x);
  }
  f(i, 1, N) {
    reg p = read();
    f(j, 1, p) add(i, read() + N, 1);
  }
  reg maxflow = 0, flow;
  while (bfs())
    while (flow = dinic(S, INF)) maxflow += flow;
  if (maxflow != sum) return puts("No Solution!"), 0;
  f(x, 1 + N, K + N) {
    printf("%d:", x - N);
    for (reg i = Head[x]; i; i = Next[i])
      if (Ver[i] != T && Edge[i]) printf(" %d", Ver[i]);
    puts("");
  }
  return 0;
}