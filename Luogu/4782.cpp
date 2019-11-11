#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline

const int SN = 2e6 + 6;
int N, M, num, scc, opp[SN], c[SN], val[SN], dfn[SN], low[SN];
int tot, Head[SN], Next[SN << 1], Ver[SN << 1];
int top, st[SN];
bool in[SN];

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void tarjan(int x) {
  dfn[x] = low[x] = ++num;
  st[++top] = x, in[x] = 1;
  for (reg i = Head[x]; i; i = Next[i])
    if (!dfn[Ver[i]]) {
      tarjan(Ver[i]);
      low[x] = min(low[x], low[Ver[i]]);
    } else if (in[Ver[i]])
      low[x] = min(low[x], dfn[Ver[i]]);
  if (dfn[x] == low[x]) {
    reg y;
    scc++;
    do {
      c[y = st[top--]] = scc;
      in[y] = 0;
    } while (y != x);
  }
}

int main() {
  scanf("%d%d", &N, &M);
  tot = 1;
  f(m, 1, M) {
    reg i, a, j, b;
    scanf("%d%d%d%d", &i, &a, &j, &b);
    add(i + (a ^ 1) * N, j + b * N), add(j + (b ^ 1) * N, i + a * N);
  }
  f(i, 1, 2 * N) if (!dfn[i]) tarjan(i);
  f(i, 1, N) if (c[i] == c[N + i]) {
    puts("IMPOSSIBLE");
    return 0;
  }
  else opp[i] = i + N, opp[i + N] = i;
  puts("POSSIBLE");
  f(i, 1, N) printf("%d ", c[i] > c[opp[i]]);
  puts("");
}