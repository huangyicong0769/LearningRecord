#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 150000, SM = 6 * SN, INF = 0x3f3f3f3f;
int N, K, A, B, C, S, T, d[SN], flow[SN], mark[SN],  //
    tot, Head[SN], Ver[SM << 1], Next[SM << 1], Edge[SM << 1], Weigh[SM << 1];
bool in[SN];

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il void add(int x, int y, int z, int w) {
  Ver[++tot] = y, Next[tot] = Head[x], Edge[tot] = z, Weigh[tot] = w, Head[x] = tot;
  Ver[++tot] = x, Next[tot] = Head[y], Edge[tot] = 0, Weigh[tot] = -w, Head[y] = tot;
}

il bool spfa() {
  ms(d, 0x3f), ms(flow, 0x3f), ms(in, 0);
  queue<int> q;
  d[S] = 0, flow[S] = INF, in[S] = 1, q.push(S);
  while (q.size()) {
    reg x = q.front(); q.pop(), in[x] = 0;
    for (reg i = Head[x]; i; i = Next[i]){
      reg y = Ver[i];
      if (d[y] > d[x] + Weigh[i] && Edge[i]){
        d[y] = d[x] + Weigh[i];
        flow[y] = min(flow[x], Edge[i]);
        mark[y] = i;
        if (!in[y]) in[y] = 1, q.push(y);
      }
    }
  }
  return d[T] != INF;
}

il int mcmf() {
  reg minCost = 0, maxflow = 0;
  while (spfa()) {
    for (reg x = T, i = mark[x]; x != S; x = Ver[i ^ 1], i = mark[x])
      Edge[i] -= flow[T], Edge[i ^ 1] += flow[T];
    // printf("%d %d\n", d[T], flow[T]);
    minCost += d[T] * flow[T];
    maxflow += flow[T];
  }
  return minCost;
}

int main() {
  N = read(), K = read(), A = read(), B = read(), C = read();
  S = N * N * (K + 1) + 1, T = S + 1, tot = 1;
  add(S, 1 + K * N * N, 1, 0);
  f(i, 0, K) add((i + 1) * N * N, T, 1, 0);
  f(i, 1, N) f(j, 1, N) {
    reg a = read(), cur = (i - 1) * N + j;
    if (a) f(k, 0, K - 1) add(cur + k * N * N, cur + K * N * N, 1, A);
    f(k, 1, K) {
      if (a && k < K) continue;
      if (i + 1 <= N) add(cur + k * N * N, cur + N + (k - 1) * N * N, INF, 0);
      if (j + 1 <= N) add(cur + k * N * N, cur + 1 + (k - 1) * N * N, INF, 0);
      if (i - 1) add(cur + k * N * N, cur - N + (k - 1) * N * N, INF, B);
      if (j - 1) add(cur + k * N * N, cur - 1 + (k - 1) * N * N, INF, B);
    }
    add(cur, cur + K * N * N, 1, A + C);
  }
  printf("%d\n", mcmf());
}
