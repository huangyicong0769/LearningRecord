#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 2 * 50 * 50 + 6, SM = 10 * SN + 6;
int S, T, N, K, tot, ans, Head[SN], Next[SM], Ver[SM], Wei[SM], Cap[SM],
    pre[SN], d[SN], incf[SN];
bool v[SN];

il int ec(int x, int y, int k) { return (x - 1) * N + y + k * N * N; }

il void add(int x, int y, int z, int c) {
  Ver[++tot] = y, Wei[tot] = z, Cap[tot] = c, Next[tot] = Head[x],
  Head[x] = tot;
  Ver[++tot] = x, Wei[tot] = -z, Cap[tot] = 0, Next[tot] = Head[y],
  Head[y] = tot;
}

il bool spfa() {
  queue<int> q;
  ms(d, 0xcf);
  ms(v, 0);
  q.push(S), d[S] = 0, v[S] = 1, incf[S] = 1 << 30;
  while (q.size()) {
    reg x = q.front();
    v[x] = 0;
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]) {
      if (!Cap[i]) continue;
      reg y = Ver[i];
      if (d[y] < d[x] + Wei[i]) {
        d[y] = d[x] + Wei[i];
        incf[y] = min(incf[x], Cap[i]);
        pre[y] = i;
        if (!v[y]) v[y] = 1, q.push(y);
      }
    }
  }
  return d[T] == 0xcfcfcfcf ? false : true;
}

il void update() {
  for (reg x = T, i = pre[x]; x != S; x = Ver[i ^ 1], i = pre[x]) {
    Cap[i] -= incf[T];
    Cap[i ^ 1] += incf[T];
  }
  ans += d[T] * incf[T];
}

int main() {
  scanf("%d%d", &N, &K);
  S = 1, T = 2 * N * N;
  tot = 1;
  f(i, 1, N) f(j, 1, N) {
    reg a;
    scanf("%d", &a);
    add(ec(i, j, 0), ec(i, j, 1), a, 1);
    add(ec(i, j, 0), ec(i, j, 1), 0, K - 1);
    if (i < N) add(ec(i, j, 1), ec(i + 1, j, 0), 0, K);
    if (j < N) add(ec(i, j, 1), ec(i, j + 1, 0), 0, K);
  }
  while (spfa()) update();
  printf("%d\n", ans);
}
