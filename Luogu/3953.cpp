#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define mp(a, b) make_pair(a, b)

const int SN = 100006, SM = SN << 1, SK = 56, INF = (1 << 31) - 1;
struct Graph {
  int tot, Head[SN], Ver[SM], Next[SM], Weigth[SM];
  il void add(int u, int v, int w) {
    Ver[++tot] = v, Weigth[tot] = w, Next[tot] = Head[u], Head[u] = tot;
  }
} fg, bg;
int N, M, K, P, disN[SN], f[SN][SK];
bool in[SN][SK];

il void Dijkstra() {
  priority_queue<pair<int, int> > pq;
  pq.push(mp(0, N));
  ms(disN, 0x7F);
  disN[N] = 0;
  while (pq.size()) {
    // while (pq.top().first != -disN[pq.top().second]) pq.pop();
    reg x = pq.top().second;
    pq.pop();
    for (reg i = bg.Head[x]; i; i = bg.Next[i]) {
      reg y = bg.Ver[i], z = bg.Weigth[i];
      if (disN[y] > disN[x] + z) {
        disN[y] = disN[x] + z;
        pq.push(mp(-disN[y], y));
      }
    }
  }
}
int dfs(int x, int k) {
  if (in[x][k]) return -1;
  if (f[x][k]) return f[x][k];
  in[x][k] = 1;
  f[x][k] = x == N ? 1 : 0;
  for (reg i = fg.Head[x]; i; i = fg.Next[i]) {
    reg y = fg.Ver[i], z = fg.Weigth[i], t = disN[y] + z - disN[x];
    if (k >= t) {
      reg v = dfs(y, k - t);
      if (v == -1) return f[x][k] = -1;
      (f[x][k] += v) %= P;
    }
  }
  in[x][k] = 0;
  return f[x][k];
}

int main() {
  reg T;
  scanf("%d", &T);
  while (T--) {
    fg.tot = bg.tot = 0;
    ms(fg.Head, 0), ms(bg.Head, 0);
    scanf("%d%d%d%d", &N, &M, &K, &P);
    f(i, 1, M) {
      reg u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      fg.add(u, v, w);
      bg.add(v, u, w);
    }
    Dijkstra();
    ms(in, 0), ms(f, 0);
    printf("%d\n", dfs(1, K));
  }
}