#include <iostream>
#include <cstdio>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline

const int SN = 2006, SM = 3000010;
int N, tot, top, cnt, S[SN], T[SN], D[SN], Head[SN], Ver[SM], Next[SM], dfn[SN],
    low[SN], st[SN], opp[SN], c[SN];
bool ins[SN];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

il bool check(const int &a, const int &b, const int &c, const int &d) {
  if (a >= c && a < d || b > c && b <= d || a <= c && b >= d) return 1;
  return 0;
}

void tarjan(const int &x) {
  dfn[x] = low[x] = ++tot;
  st[++top] = x, ins[x] = 1;
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (!dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (ins[y])
      low[x] = min(low[x], dfn[y]);
  }
  if (dfn[x] == low[x]) {
    reg z;
    ++cnt;
    do {
      z = st[top--];
      c[z] = cnt;
      ins[z] = 0;
    } while (x != z);
  }
}

int main() {
  scanf("%d", &N);
  f(i, 1, N) {
    reg sh, sm, th, tm;
    scanf("%d:%d %d:%d %d", &sh, &sm, &th, &tm, &D[i]);
    S[i] = sh * 60 + sm, T[i] = th * 60 + tm;
  }
  f(i, 1, N - 1) f(j, i + 1, N) {
    if (check(S[i], S[i] + D[i], S[j], S[j] + D[j]))
      add(i, j + N), add(j, i + N);
    if (check(S[i], S[i] + D[i], T[j] - D[j], T[j]))
      add(i, j), add(j + N, i + N);
    if (check(T[i] - D[i], T[i], S[j], S[j] + D[j]))
      add(i + N, j + N), add(j, i);
    if (check(T[i] - D[i], T[i], T[j] - D[j], T[j]))
      add(i + N, j), add(j + N, i);
  }
  f(i, 1, 2 * N) if (!dfn[i]) tarjan(i);
  f(i, 1, N) {
    if (c[i] == c[i + N]) {
      puts("NO");
      return 0;
    }
    opp[i] = N + i, opp[N + i] = i;
  }
  puts("YES");
  f(i, 1, N) if (c[i] > c[opp[i]])
      printf("%02d:%02d %02d:%02d\n", (T[i] - D[i]) / 60, (T[i] - D[i]) % 60,
             T[i] / 60, T[i] % 60);
  else printf("%02d:%02d %02d:%02d\n", S[i] / 60, S[i] % 60, (S[i] + D[i]) / 60,
              (S[i] + D[i]) % 60);
}