#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define il inline

const int SN = 106, inf = 0x3fffffff;
int S, T, N, M, tot, Head[SN], Next[SN * SN * 2], Edge[SN * SN * 2],
    Ver[SN * SN * 2], d[SN], u[SN * SN * 2], v[SN * SN * 2];

il int read() {
  reg x = 0;
  register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar())
    if (ch == EOF) return EOF;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il void add(int x, int y, int z) {
  Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
  Ver[++tot] = x, Edge[tot] = 0, Next[tot] = Head[y], Head[y] = tot;
}

il bool bfs() {
  ms(d, 0);
  queue<int> q;
  q.push(S), d[S] = 1;
  while (q.size()) {
    reg x = q.front();
    // cout << 'b'<< x << endl;
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]) {
      if (!Edge[i] || d[Ver[i]]) continue;
      d[Ver[i]] = d[x] + 1;
      if (Ver[i] == T) return true;
      q.push(Ver[i]);
    }
  }
  return false;
}

int dinic(int x, int flow) {
  // cout << 'd'<< x << endl;
  if (x == T) return flow;
  reg rest = flow;
  for (reg i = Head[x]; i && rest; i = Next[i]) {
    if (!Edge[i] || d[Ver[i]] != d[x] + 1) continue;
    reg k = dinic(Ver[i], min(rest, Edge[i]));
    if (!k) d[Ver[i]] = 0;
    rest -= k;
    Edge[i] -= k;
    Edge[i ^ 1] += k;
  }
  return flow - rest;
}

int main() {
  cin >> N;
  while (cin >> N >> M) {
    // printf("%d %d\n", N, M);
    f(i, 1, M) u[i] = read() + 1, v[i] = read() + 1;
    // cout << "!" << endl;
    reg ans = inf;
    f(s, 1, N) f(t, 1, N) if (s != t) {
      // cout << s << ' ' << t << endl;
      S = s, T = t;
      ms(Head, 0);
      tot = 1;
      f(i, 1, N)(i == S || i == T) ? add(i, i + N, inf) : add(i, i + N, 1);
      f(i, 1, M) add(u[i] + N, v[i], inf), add(v[i] + N, u[i], inf);
      reg flow = 0, maxflow = 0;
      while (bfs())
        while (flow = dinic(S, inf)) maxflow += flow;
      ans = min(ans, maxflow);
    }
    if (N <= 1 || ans == inf) ans = N;
    printf("%d\n", ans);
  }
}