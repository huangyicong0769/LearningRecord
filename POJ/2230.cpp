#include <cstdio>
#include <iostream>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SI = 10006;
int N, M, tot, Head[SI], Ver[SI * 5 << 1], Next[SI * 5 << 1], ans[SI * 5 << 1],
    stack[SI * 5 << 1];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

int main() {
  scanf("%d%d", &N, &M);
  tot = 1;
  f(i, 1, M) {
    reg x, y;
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  reg top = 0, t = 0;
  stack[++top] = 1;
  while (top) {
    reg x = stack[top], i = Head[x];
    // for (; i; i = Next[i]);
    if (i) stack[++top] = Ver[i], Head[x] = Next[i];
    else top--, ans[++t] = x;
  }
  for (reg i = t; i; i--) printf("%d\n", ans[i]);
}