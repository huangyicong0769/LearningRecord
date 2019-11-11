#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 3e5 + 6;
int N, M, num, ret, maxlen, fa[SN], dep[SN], sum[SN], len[SN];
bool vis[SN];
struct Graph {
  int tot, Head[SN], Ver[SN << 1], Edge[SN << 1], Next[SN << 1];
  inline void add(int x, int y, int z) {
    Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
  }
  inline void add(int x, int y) {
    Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
  }
} G, Q;
struct Rath {
  int u, v, dis, lca;
} R[SN];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar());
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}
void dfs(int x, int pre) {
  for (reg i = G.Head[x]; i; i = G.Next[i]) {
    reg y = G.Ver[i];
    if (y == pre) continue;
    dfs(y, x);
    sum[x] += sum[y];
  }
  if (sum[x] == num && len[x] > ret) ret = len[x];
}
inline bool check(int x) {
  ms(sum, 0);
  num = ret = 0;
  f(i, 1, M) if (R[i].dis > x) {
    sum[R[i].u]++;
    sum[R[i].v]++;
    sum[R[i].lca] -= 2;
    num++;
  }
  dfs(1, 0);
  return maxlen - ret <= x;
}
void tarjan(int x, int pre) {
  for (reg i = G.Head[x]; i; i = G.Next[i]) {
    reg y = G.Ver[i], z = G.Edge[i];
    if (y == pre) continue;
    dep[y] = dep[x] + z;
    tarjan(y, x);
    len[y] = z;
    reg faX = find(x), faY = find(y);
    if (faX != faY) fa[faY] = faX;
    vis[y] = 1;
  }
  for (reg i = Q.Head[x]; i; i = Q.Next[i]) {
    reg y = Q.Ver[i], p = i >> 1;
    if (!vis[y]) continue;
    R[p].lca = find(y);
    R[p].dis = dep[x] + dep[y] - 2 * dep[R[p].lca];
    maxlen = max(maxlen, R[p].dis);
  }
}
int main() {
  N = read(), M = read();
  f(i, 1, N) fa[i] = i;
  f(i, 2, N) {
    reg a = read(), b = read(), t = read();
    G.add(a, b, t), G.add(b, a, t);
  }
  Q.tot = 1;
  f(i, 1, M) {
    R[i].u = read(), R[i].v = read();
    Q.add(R[i].u, R[i].v), Q.add(R[i].v, R[i].u);
  }
  // cout << '!' << endl;
  tarjan(1, 0);
  reg l = 0, r = maxlen, ans = 0;
  while (l <= r) {
    reg mid = (l + r) >> 1;
    if (check(mid)) {
      r = mid - 1;
      ans = mid;
    } else
      l = mid + 1;
  }
  printf("%d\n", ans);
}