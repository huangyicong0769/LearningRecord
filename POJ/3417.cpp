#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SIZE = 1e5 + 6;
int N, M, T, fa[SIZE][20], d[SIZE], f[SIZE], ans;
bool b[SIZE];
vector<int> v[SIZE];

il void preWork() {
  queue<int> q;
  q.push(1);
  d[1] = 1;
  while (q.size()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < v[x].size(); i++) {
      int y = v[x][i];
      if (d[y]) continue;
      d[y] = d[x] + 1;
      fa[y][0] = x;
      for (int j = 1; j <= T; j++) fa[y][j] = fa[fa[y][j - 1]][j - 1];
      q.push(y);
    }
  }
}

il int LCA(int x, int y) {
  if (d[x] < d[y]) swap(x, y);
  for (reg i = T; i >= 0; i--)
    if (d[fa[x][i]] >= d[y]) x = fa[x][i];
  if (x == y) return y;
  for (reg i = T; i >= 0; i--)
    if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

void dfs(int x) {
  b[x] = 1;
  f(i, 0, (int)v[x].size() - 1) {
    const reg &y = v[x][i];
    if (b[y]) continue;
    dfs(y);
    f[x] += f[y];
  }
  if (f[x] == 0) ans += M;
  if (f[x] == 1) ans++;
}

int main() {
  scanf("%d%d", &N, &M);
  T = (int)(log(N) / log(2)) + 1;
  f(i, 2, N) {
    reg a, b;
    scanf("%d%d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
  }
  preWork();
  f(i, 1, M) {
    reg x, y;
    scanf("%d%d", &x, &y);
    f[x]++, f[y]++, f[LCA(x, y)] -= 2;
  }
  dfs(1);
  printf("%d\n", ans - M);
}