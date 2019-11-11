#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 106, INF = 0x3f3f3f3f;
int N, S, T, a[SN], flow[SN], last[SN], dis[SN], mark[SN], //
    tot, Head[SN], Ver[SN << 2], Next[SN << 2], Edge[SN << 2], Weigh[SN << 2];
bool in[SN];

il int read() {
  reg x = 0;
  register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il void add(int a, int b, int c, int d) {
  Ver[++tot] = b, Edge[tot] = c, Weigh[tot] = d, Next[tot] = Head[a],
  Head[a] = tot;
  Ver[++tot] = a, Edge[tot] = 0, Weigh[tot] = -d, Next[tot] = Head[b],
  Head[b] = tot;
}

// int cnt = 0;
il bool spfa() {
  queue<int> q;
  ms(dis, 0x3f), ms(in, 0), ms(flow, 0x3f);
  q.push(S), dis[S] = 0, in[S] = 1, last[T] = 0;
  while (q.size()) {
    reg a = q.front();
    q.pop(), in[a] = 0;
    // printf("%d\n", a);
    // if (++cnt > 30) break;
    for (reg i = Head[a]; i; i = Next[i]) {
      reg b = Ver[i], c = Edge[i], d = Weigh[i];
      // printf(" %d %d %d %d\n", a, b, c, d);
      if (dis[b] <= dis[a] + d || c == 0) continue;
      dis[b] = dis[a] + d;
      flow[b] = min(flow[a], c);
      mark[b] = i;
      last[b] = a;
      if (!in[b]) in[b] = 1, q.push(b);
    }
  }
  return last[T] != 0;
}

/* bool spfa() {
  memset(in, 0, sizeof(in));
  memset(dis, 20010509, sizeof(dis));
  memset(flow, 20010509, sizeof(flow));
  queue<int> ready;
  ready.push(S);
  dis[S] = 0;
  in[S] = 1;
  // flow[s] = 20010509;
  last[T] = 0;
  while (!ready.empty()) {
    reg ndo = ready.front();
    ready.pop();
    in[ndo] = 0;
    for (int i = Head[ndo]; i; i = Next[i]) {
      if (dis[Ver[i]] <= dis[ndo] + Weigh[i] || Edge[i] == 0) continue;
      dis[Ver[i]] = dis[ndo] + Weigh[i];
      flow[Ver[i]] = min(Edge[i], flow[ndo]);
      last[Ver[i]] = ndo;
      if (!in[Ver[i]]) {
        in[Ver[i]] = 1;
        ready.push(Ver[i]);
      }
    }
  }
  return last[T] != 0;
} */

int main() {
  N = read();
  reg avg = 0;
  f(i, 1, N) avg += (a[i] = read());
  avg /= N, S = N + 1, T = N + 2, tot = 1;
  f(i, 1, N) 
    if ((a[i] -= avg) < 0) add(i, T, -a[i], 0);
    else if (a[i] > 0) add(S, i, a[i], 0);
  f(i, 1, N) {
    if (i != 1) add(i, i - 1, INF, 1);
    if (i != N) add(i, i + 1, INF, 1);
  }
  add(1, N, INF, 1), add(N, 1, INF, 1);
  /*   reg sum = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    sum /= N;
    S = N + 1;
    T = N + 2;
    for (int i = 1; i <= N; ++i) a[i] -= sum;
    for (int i = 1; i <= N; ++i) {
      if (a[i] > 0)
        add(S, i, a[i], 0);
      else if (a[i] < 0)
        add(i, T, -a[i], 0);
    }
    for (int i = 1; i <= N; ++i) {
      if (i != 1) add(i, (i - 1), INF, 1);
      if (i != N) add(i, (i + 1), INF, 1);
    }
    add(1, N, INF, 1);
    add(N, 1, INF, 1); */
  reg minCost = 0, maxFlow = 0;
  while (spfa()) {
    maxFlow += flow[T];
    minCost += flow[T] * dis[T];
    for (reg x = T; x != S; x = last[x])
      Edge[mark[x]] -= flow[T], Edge[mark[x] ^ 1] += flow[T];
  }
  printf("%d\n", minCost);
}