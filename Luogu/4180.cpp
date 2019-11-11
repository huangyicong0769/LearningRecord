#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define reg register
#define f(i, s, t) for (reg int i = s; i != t + 1; i++)
#define mp(a, b) make_pair(a, b)
using namespace std;

typedef long long ll;
const int SIZE = 100006;
const ll INF = (1ll << 62);
int N, M, T, fa[SIZE][18], c[SIZE], d[SIZE];
ll g[SIZE][18][2];
bool b[SIZE], tr[3 * SIZE];
vector<pair<int, ll> > v[SIZE];
struct Edge {
  int x, y;
  ll z;
  bool operator<(const Edge& a) const { return z < a.z; }
} e[3 * SIZE];

int getFa(int x) { return c[x] == x ? x : c[x] = getFa(c[x]); }

il void preWork() {
  queue<int> q;
  q.push(1);
  d[1] = 1;
  while (q.size()) {
    reg int x = q.front();
    q.pop();
    f(i, 0, (int)v[x].size() - 1) {
      const reg int& y = v[x][i].first;
      const reg ll& z = v[x][i].second;
      if (d[y]) continue;
      fa[y][0] = x;
      d[y] = d[x] + 1;
      g[y][0][0] = z;
      g[y][0][1] = -INF;
      f(j, 1, T) {
        fa[y][j] = fa[fa[y][j - 1]][j - 1];
        g[y][j][0] = max(g[y][j - 1][0], g[fa[y][j - 1]][j - 1][0]);
        if (g[y][j - 1][0] == g[fa[y][j - 1]][j - 1][0])
          g[y][j][1] = max(g[y][j - 1][1], g[fa[y][j - 1]][j - 1][1]);
        if (g[y][j - 1][0] > g[fa[y][j - 1]][j - 1][0])
          g[y][j][1] = max(g[y][j - 1][1], g[fa[y][j - 1]][j - 1][0]);
        if (g[y][j - 1][0] < g[fa[y][j - 1]][j - 1][0])
          g[y][j][1] = max(g[y][j - 1][0], g[fa[y][j - 1]][j - 1][1]);
      }
      q.push(y);
    }
  }
}

il int lca(int x, int y, ll& val1, ll& val2) {
  val1 = -INF, val2 = -INF;
  if (d[x] < d[y]) swap(x, y);
  for (reg int i = T; i >= 0; i--)
    if (d[fa[x][i]] >= d[y]) {
      val1 = max(val1, g[x][i][0]);
      val2 = max(val2, g[x][i][1]);
      x = fa[x][i];
    }
  if (x == y) return y;
  for (reg int i = T; i >= 0; i--)
    if (fa[x][i] != fa[y][i]) {
      val1 = max(val1, max(g[x][i][0], g[y][i][0]));
      val2 = max(val2, g[x][i][0] != val1 ? g[x][i][0] : g[x][i][1]);
      val2 = max(val2, g[y][i][0] != val1 ? g[y][i][0] : g[y][i][1]);
      x = fa[x][i], y = fa[y][i];
    }
  val1 = max(val1, max(g[x][0][0], g[y][0][0]));
  val2 = max(val2, g[x][0][0] != val1 ? g[x][0][0] : g[x][0][1]);
  val2 = max(val2, g[y][0][0] != val1 ? g[y][0][0] : g[y][0][1]);
  return fa[x][0];
}

int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%d%d", &N, &M);
  T = (int)(log(N) / log(2)) + 1;
  f(i, 1, M) scanf("%d%d%lld", &e[i].x, &e[i].y, &e[i].z);
  sort(e + 1, e + 1 + M);
  f(i, 1, N) c[i] = i;
  reg ll sum = 0, val1 = 0, val2 = 0, ans = INF;
  f(i, 1, M) {
    const reg int x = getFa(e[i].x), y = getFa(e[i].y);
    if (x == y) continue;
    tr[i] = 1;
    c[x] = y;
    sum += e[i].z;
    v[e[i].x].push_back(mp(e[i].y, e[i].z));
    v[e[i].y].push_back(mp(e[i].x, e[i].z));
  }
  preWork();
  f(i, 1, M) {
    if (tr[i]) continue;
    reg int p = lca(e[i].x, e[i].y, val1, val2);
    if (e[i].z == val1) ans = min(ans, sum + e[i].z - val2);
    if (e[i].z > val1) ans = min(ans, sum + e[i].z - val1);
  }
  printf("%lld\n", ans);
}