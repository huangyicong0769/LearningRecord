#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 100006, SM = 500006;
int N, M, cnt, dfn[SN], low[SN], sccCnt, scc[SN], du[SN],  //
    tot, Head[SN], Next[SM << 1], Ver[SM << 1],            //
    top, stack[SN];
bool in[SN];

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void tarjan(int x) {
  dfn[x] = low[x] = ++cnt;
  in[x] = 1, stack[++top] = x;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
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
      in[y] = 0;
    } while (x != y);
  }
}

int main() {
  // freopen("./data/2002/1.in", "r", stdin);
  N = read(), M = read();
  f(i, 1, M) {
    reg u = read(), v = read();
    if (u != v) add(u, v);
  }
  f(i, 1, N) if (!dfn[i]) tarjan(i);
  f(x, 1, N) for (reg i = Head[x]; i; i = Next[i]) if (scc[Ver[i]] != scc[x]) du[scc[Ver[i]]]++;
  reg ans = 0;
  f(i, 1, sccCnt) if (!du[i]) ans++;
  printf("%d\n", ans);
}