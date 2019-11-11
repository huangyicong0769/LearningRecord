#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define reg register
#define f(i, s, t) for (reg int i = s; i != t + 1; i++)
#define mp(a, b) make_pair(a, b)
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;

typedef long long ll;
const int SIZE = 50006;
int N, M, T, a[SIZE], b[SIZE], e[SIZE], fa[SIZE][17];
ll c[SIZE], dis[SIZE][17], f[SIZE];
bool b1[SIZE], b2[SIZE];
vector<pair<int, int> > v[SIZE];
vector<ll> h[SIZE];

bool dfs(int x) {
  // printf("dfs:%d\n", x);
  b1[x] = 1;
  if (!e[x] && b2[x]) return 1;
  bool flag = 0;
  f(i, 0, (int)v[x].size() - 1) {
    const reg int y = v[x][i].first;
    if (b1[y]) continue;
    flag = 1;
    if (!dfs(y)) return 0;
  }
  return flag;
}

il void preWork() {
  queue<int> q;
  b1[1] = 1;
  f(i, 0, (int)v[1].size() - 1) {
    const reg int &y = v[1][i].first;
    b1[y] = 1;
    q.push(y);
    b[e[y] = ++T] = i;
  }
  while (q.size()) {
    const reg int x = q.front();
    q.pop();
    f(i, 0, (int)v[x].size() - 1) {
      const reg int &y = v[x][i].first;
      if (b1[y]) continue;
      b1[y] = 1;
      fa[y][0] = x;
      dis[y][0] = v[x][i].second;
      f(j, 1, 16) fa[y][j] = fa[fa[y][j - 1]][j - 1],
                  dis[y][j] = dis[y][j - 1] + dis[fa[y][j - 1]][j - 1];
      q.push(y);
    }
  }
}

il bool work(const ll &limit) {
  // printf("trying%lld\n", limit);
  ms(b1, 0), ms(b2, 0);
  f(i, 1, T) h[i].clear();
  b1[1] = 1;
  f(i, 1, M) {
    reg ll g = a[i], d = 0;
    for (reg int j = 16; j >= 0; j--)
      if (fa[g][j] && d + dis[g][j] <= limit)  d += dis[g][j], g = fa[g][j];
    b2[g] = 1;
    const reg int &j = e[g];
    if (j) {
      h[j].push_back(limit - d);
      if (h[j].size() > 1 && limit - d > *(h[j].end() - 2))
        swap(h[j][h[j].size() - 1], h[j][h[j].size() - 2]);
    }
  }
  reg int p = 0, q = 0;
  f(i, 1, T) {
    // printf("counting%d\n", i);
    if (!dfs(v[1][b[i]].first)) {
      if (h[i].size() && h[i].back() < v[1][b[i]].second << 1)
        h[i].pop_back();
      else
        f[++p] = v[1][b[i]].second;
    }
    // puts("!1");
    f(j, 0, (int)h[i].size() - 1) if (h[i][j] >= v[1][b[i]].second) c[++q] =
        h[i][j] - v[1][b[i]].second;
    // puts("!2");
  }
  // puts("counting finish");
  sort(f + 1, f + 1 + p);
  sort(c + 1, c + 1 + q);
  if (p > q) return 0;
  for (reg int i = p, j = q; i; i--, j--)
    if (c[j] < f[i]) return 0;
  return 1;
}

int main() {
  reg ll sum = 0;
  scanf("%d", &N);
  f(i, 2, N) {
    reg int U, V, W;
    scanf("%d%d%d", &U, &V, &W);
    v[U].push_back(mp(V, W));
    v[V].push_back(mp(U, W));
    sum += W;
  }
  scanf("%d", &M);
  f(i, 1, M) scanf("%d", &a[i]);
  preWork();
  reg ll l = 0, r = sum + 1;
  while (l < r) {
    reg ll mid = (l + r) >> 1;
    work(mid) ? r = mid : l = mid + 1;
  }
  l > sum ? puts("−1") : printf("%lld\n", l);
}