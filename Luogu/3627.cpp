#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 500006, INF = 0x7f7f7f7f;
int N, M, S, P, A[SN], cnt, dfn[SN], low[SN],  //
    sccCnt, scc[SN], dis[SN], sum[SN],         //
    top, stack[SN];
bool in[SN];
struct Graph {
  int tot, Head[SN], Ver[SN], Next[SN], Edge[SN];
  il void add(int x, int y, int z) {
    Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
  }
} g1, g2;

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

void tarjan(int x) {
  dfn[x] = low[x] = ++cnt;
  stack[++top] = x, in[x] = 1;
  for (reg i = g1.Head[x]; i; i = g1.Next[i]) {
    reg y = g1.Ver[i];
    if (!dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (in[y])
      low[x] = min(low[x], dfn[y]);
  }
  if (dfn[x] == low[x]) {
    reg y;
    sccCnt++;
    do {
      y = stack[top--];
      scc[y] = sccCnt;
      sum[sccCnt] += A[y];
      in[y] = 0;
    } while (y != x);
  }
}

il void spfa() {
  queue<int> q;
  ms(in, 0), ms(dis, 0x7f), q.push(scc[S]), in[scc[S]] = 1;
  dis[scc[S]] = -sum[scc[S]];
  while (q.size()) {
    reg x = q.front();
    q.pop(), in[x] = 0;
    for (reg i = g2.Head[x]; i; i = g2.Next[i]) {
      reg y = g2.Ver[i], z = g2.Edge[i];
      if (dis[y] <= dis[x] + z) continue;
      dis[y] = dis[x] + z;
      if (!in[y]) in[y] = 1, q.push(y);
    }
  }
}

int main(int argc, const char** argv) {
  // freopen("./data/3627/3.in", "r", stdin);
  N = read(), M = read();
  f(i, 1, M) {
    reg x = read(), y = read();
    g1.add(x, y, 0);
  }
  f(i, 1, N) A[i] = read();
  f(i, 1, N) if (!dfn[i]) tarjan(i);
  // f(i, 1, N) printf("%d ", scc[i]); puts("");
  // puts("");
  f(x, 1, N) for (reg i = g1.Head[x]; i; i = g1.Next[i]) {
    reg y = g1.Ver[i];
    if (scc[x] == scc[y]) continue;
    g2.add(scc[x], scc[y], -sum[scc[y]]);
    // printf("%d %d %d\n", scc[x], scc[y], -sum[scc[y]]);
  }
  S = read(), spfa(), P = read();
  reg ans = 0;
  f(i, 1, P) ans = max(ans, -dis[scc[read()]]);
  printf("%d\n", ans);
  return 0;
}