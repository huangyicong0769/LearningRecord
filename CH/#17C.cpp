#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define fg(i, x) for (reg i = Head[x]; i; i = Next[i])
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 40006, SM = 200006, inf = 0x3fffffff;
int N, M, E, S, T, tot, scc, top, num, Head[SN], Next[SM], Ver[SM], Edge[SM],
    d[SN], dfn[SN], low[SM], c[SN], st[SN], e[SN];
bool ins[SN];
vector<int> a[SN];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Edge[tot] = 1, Next[tot] = Head[x], Head[x] = tot;
  Ver[++tot] = x, Edge[tot] = 0, Next[tot] = Head[y], Head[y] = tot;
}
il bool bfs() {
  ms(d, 0);
  queue<int> q;
  q.push(S), d[S] = 1;
  while (q.size()) {
    const reg x = q.front();
    q.pop();
    fg(i, x) {
      if (!Edge[i] || d[Ver[i]]) continue;
      d[Ver[i]] = d[x] + 1;
      if (Ver[i] == T) return 1;
      q.push(Ver[i]);
    }
  }
  return 0;
}
int dinic(int x, int flow) {
  if (x == T) return flow;
  reg rest = flow;
  for (reg i = Head[x]; i && rest; i = Next[i]) {
    if (!Edge[i] || d[Ver[i]] != d[x] + 1) continue;
    reg k = dinic(Ver[i], min(rest, Edge[i]));
    if (!k) d[Ver[i]] = 0;
    Edge[i] -= k;
    Edge[i ^ 1] += k;
    rest -= k;
  }
  return flow - rest;
}
void tarjan(const int &x) {
  dfn[x] = low[x] = ++num;
  st[++top] = x, ins[x] = 1;
  f(i, 0, (int)a[x].size() - 1) {
    const reg &y = a[x][i];
    if (!dfn[y])
      tarjan(y), low[x] = min(low[x], low[y]);
    else if (ins[y])
      low[x] = min(low[x], dfn[y]);
  }
  if (low[x] == dfn[x]) {
    reg z;
    scc++;
    do {
      z = st[top--], ins[z] = 0, c[z] = scc;
    } while (z != x);
  }
}

int main() {
  scanf("%d%d%d", &N, &M, &E);
  tot = 1;
  S = 0, T = N + M + 1;
  f(i, 1, N) add(S, i);
  f(i, 1, M) add(i + N, T);
  f(i, 1, E) {
    reg x, y;
    scanf("%d%d", &x, &y);
    add(x, y + N), e[i] = tot;
  }
  reg flow = 0, maxflow = 0;
  while (bfs())
    while (flow = dinic(S, inf)) maxflow += flow;
  f(i, 1, E) if (Edge[e[i]]) a[Ver[e[i] ^ 1]].push_back(Ver[e[i]]);
  else a[Ver[e[i]]].push_back(Ver[e[i] ^ 1]);
  f(i, 1, N) if (Edge[i * 2]) a[S].push_back(i);
  else a[i].push_back(S);
  f(i, 1, M) if (Edge[2 * (i + N)]) a[N + i].push_back(T);
  else a[T].push_back(N + i);
  f(i, 1, T) if (!dfn[i]) tarjan(i);
  reg cnt = 0;
  f(i, 1, E) if (Edge[e[i]] || c[Ver[e[i]]] == c[Ver[e[i] ^ 1]]) cnt++;
  cnt = E - cnt;
  printf("%d\n", cnt);
  f(i, 1, E) {
    if (Edge[e[i]] || c[Ver[e[i]]] == c[Ver[e[i] ^ 1]]) continue;
    printf("%d ", i);
  }
  puts("");
}