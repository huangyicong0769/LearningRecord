#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define mp(a, b) make_pair(a, b)
using namespace std;

const int SIZE = 100006;
int N, K, fa[SIZE], d[SIZE];
bool b[SIZE];
vector<pair<int, int> > v[SIZE];
vector<int> path;

void dfs(int x, int& t) {
  b[x] = 1;
  f(i, 0, (int)v[x].size() - 1) {
    const reg& y = v[x][i].first;
    if (b[y]) continue;
    d[y] = d[x] + v[x][i].second;
    if (d[y] >= d[t]) t = y;
    fa[y] = x;
    dfs(y, t);
  }
  b[x] = 0;
}

void dp(int x, int& t) {
  b[x] = 1;
  f(i, 0, (int)v[x].size() - 1) {
    const reg& y = v[x][i].first;
    if (b[y]) continue;
    dp(y, t);
    t = max(t, d[x] + d[y] + v[x][i].second);
    d[x] = max(d[x], d[y] + v[x][i].second);
  }
  b[x] = 0;
}

int main() {
  scanf("%d%d", &N, &K);
  f(i, 2, N) {
    reg a, b;
    scanf("%d%d", &a, &b);
    v[a].push_back(mp(b, 1));
    v[b].push_back(mp(a, 1));
  }
  reg t = 1;
  dfs(1, t);
  d[t] = fa[t] = 0;
  reg tt = t;
  dfs(t, tt);
  // f(i, 1, N) printf("%d ", fa[i]);
  // puts("");
  // printf("%d--%d\n", t, tt);
  reg ans = ((N - 1) << 1) - d[tt] + 1;
  if (K == 2) {
    for (; fa[tt]; tt = fa[tt]) {
      // f(i, 0, (int)v[tt].size() - 1) 
      //   if (v[tt][i].first == fa[tt]) v[tt][i].second = -1;
      f(i, 0, (int)v[fa[tt]].size() - 1) 
        if (v[fa[tt]][i].first == tt) v[fa[tt]][i].second = -1;
      // printf("%d\n", tt);
    }
    // f(i, 1, N) {
    //   f(j, 0, (int)v[i].size() - 1)
    //       printf("%d, %d; ", v[i][j].first, v[i][j].second);
    //   puts("");
    // }
    tt = 0;
    memset(d, 0, sizeof(d));
    dp(t, tt);
    ans -= tt - 1;
  }
  printf("%d\n", ans);
}