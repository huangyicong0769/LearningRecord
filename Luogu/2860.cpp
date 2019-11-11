#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline

const int SN = 5006, SM = 20006;
int N, M, dcc, num, c[SN], dfn[SN], low[SN], v[SN], du[SN];
int tot, Head[SN], Next[SM], Ver[SM];
bool br[SM];

il void add(int a, int b) {
  Ver[++tot] = b, Next[tot] = Head[a], Head[a] = tot;
}
void tarjan(int x, int la) {
  dfn[x] = low[x] = ++num;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (!dfn[y]) {
      tarjan(y, i);
      low[x] = min(low[x], low[y]);
      if (dfn[x] < low[y]) br[i] = br[i ^ 1] = 1;
    } else if (i != (la ^ 1))
      low[x] = min(low[x], dfn[y]);
  }
}
void dfs1(int x) {
  c[x] = dcc;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (c[y] || br[i]) continue;
    dfs1(y);
  }
}

int main() {
  scanf("%d%d", &N, &M);
  tot = 1;
  f(i, 1, M) {
    reg a, b;
    scanf("%d%d", &a, &b);
    add(a, b), add(b, a);
  }
  tarjan(1, 0);
  f(i, 1, N) if (!c[i])++ dcc, dfs1(i);
  f(i, 2, tot) {
    reg x = Ver[i ^ 1], y = Ver[i];
    if (c[x] == c[y]) continue;
    du[c[y]]++;
  }
  reg leaf = 0;
  f(i, 1, dcc) if (du[i] == 1) leaf++;
  printf("%d\n", (leaf + 1) / 2);
}