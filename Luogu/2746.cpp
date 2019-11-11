#include <cstdio>
#include <iostream>
#include <vector>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SI = 10006, SJ = 5000006;
int N, M, tot, cnt, tc, num, top, Head[SI], Ver[SJ], Next[SJ], dfn[SI], low[SI],
    stack[SI], c[SI], in[SI], out[SI];
bool ins[SI];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void tarjan(const int x) {
  dfn[x] = low[x] = ++num;
  stack[++top] = x, ins[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (!dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (ins[y])
      low[x] = min(low[x], dfn[y]);
  }
  if (dfn[x] == low[x]) {
    reg y;
    ins[x] = 0, c[x] = ++cnt;
    do
      y = stack[top--], ins[y] = 0, c[y] = cnt;
    while (x != y);
  }
}

int main() {
  scanf("%d", &N);
  f(i, 1, N) {
    reg t;
    for (scanf("%d", &t); t; scanf("%d", &t)) add(i, t);
  }
  f(i, 1, N) if (!dfn[i]) tarjan(i);
  f(x, 1, N) for (reg i = Head[x]; i; i = Next[i]) if (c[x] != c[Ver[i]])
      in[c[Ver[i]]]++,
      out[c[x]]++;
  reg p = 0, q = 0;
  f(i, 1, cnt) {
    if (!in[i]) p++;
    if (!out[i]) q++;
  }
  printf("%d\n", p);
  cnt == 1 ? puts("0") : printf("%d\n", max(p, q));
}