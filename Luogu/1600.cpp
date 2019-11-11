#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SIZE = 300000;
int N, M, T, c1[SIZE << 1], c2[SIZE << 1], d[SIZE], fa[SIZE][20], w[SIZE],
    ans[SIZE];
vector<int> v[SIZE], a1[SIZE], a2[SIZE], b1[SIZE], b2[SIZE];

il void preWork() {
  queue<int> q;
  q.push(1);
  d[1] = 1;
  while (q.size()) {
    reg x = q.front();
    q.pop();
    f(i, 0, (int)v[x].size() - 1) {
      reg y = v[x][i];
      if (d[y]) continue;
      d[y] = d[x] + 1;
      fa[y][0] = x;
      f(j, 1, T) fa[y][j] = fa[fa[y][j - 1]][j - 1];
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
  reg cnt1 = c1[w[x] + d[x]], cnt2 = c2[w[x] - d[x] + SIZE];
  f(i, 0, (int)v[x].size() - 1) {
    reg y = v[x][i];
    if (y == fa[x][0]) continue;
    dfs(y);
  }
  f(i, 0, (int)a1[x].size() - 1) c1[a1[x][i]]++;
  f(i, 0, (int)b1[x].size() - 1) c1[b1[x][i]]--;
  f(i, 0, (int)a2[x].size() - 1) c2[a2[x][i] + SIZE]++;
  f(i, 0, (int)b2[x].size() - 1) c2[b2[x][i] + SIZE]--;
  ans[x] += c1[w[x] + d[x]] - cnt1 + c2[w[x] - d[x] + SIZE] - cnt2;
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
  f(i, 1, N) scanf("%d", &w[i]);
  f(i, 1, M) {
    reg s, t;
    scanf("%d%d", &s, &t);
    reg p = LCA(s, t);
    a1[s].push_back(d[s]);
    b1[fa[p][0]].push_back(d[s]);
    a2[t].push_back(d[s] - 2 * d[p]);
    b2[p].push_back(d[s] - 2 * d[p]);
  }
  dfs(1);
  f(i, 1, N) printf("%d ", ans[i]);
  puts("");
}