#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define mp(a, b) make_pair(a, b)
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;

const int SIZE = 1006;
int N, S, d[SIZE], fa[SIZE], q[SIZE], f[SIZE];
bool b[SIZE];
vector<pair<int, int> > v[SIZE];
vector<int> path;

void dfs(int x) {
  f(i, 0, (int)v[x].size() - 1) {
    const reg &y = v[x][i].first;
    if (y == fa[x]) continue;
    d[y] = d[x] + v[x][i].second;
    fa[y] = x;
    dfs(y);
  }
}

void dp(int x) {
  b[x] = 1;
  f(i, 0, (int)v[x].size() - 1) {
    const reg &y = v[x][i].first;
    if (b[y]) continue;
    dp(y);
    f[x] = max(f[x], f[y] + v[x][i].second);
  }
}

int main() {
  scanf("%d%d", &N, &S);
  f(i, 2, N) {
    reg a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    v[a].push_back(mp(b, c));
    v[b].push_back(mp(a, c));
  }
  dfs(1);
  reg s = 1;
  f(i, 2, N) if (d[i] > d[s]) s = i;
  d[s] = 0;
  ms(fa, 0);
  dfs(s);
  reg t = 1;
  f(i, 2, N) if (d[i] > d[t]) t = i;
  for (reg i = t; i != s; i = fa[i]) {
    b[i] = 1;
    path.push_back(i);
  }
  b[s] = 1;
  path.push_back(s);
  reverse(path.begin(), path.end());
  f(i, 0, (int)path.size() - 1) dp(path[i]);
  reg ans = (1 << 31) - 1, tmp = 0, j = - 1;
  f(i, 0, (int)path.size() - 1) tmp = max(tmp, f[path[i]]);
  f(i, 0, (int)path.size() - 1) {
    while (j + 1 < path.size() && d[path[j + 1]] - d[path[i]] <= S) j++;
    ans = min(ans, max(tmp, max(d[path[i]], d[path.back()] - d[path[j]])));
  }
  printf("%d\n", ans);
}