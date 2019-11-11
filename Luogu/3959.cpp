#pragma GCC optimize(3, "Ofast", "inline")
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define mp(a, b) make_pair(a, b)

const int SN = 15, INF = 0x7f7f7f7f;
int N, M, ans, th, g[SN][SN], dis[SN];
bool in[SN];
vector<pair<int, int> > v[SN];
vector<int> vis;

void dfs(int cnt, int num, int t1, int t2) {
  // printf("%d %d\n  ", cnt, num);
  // f(i, 1, N) if (in[i]) printf("%d ", i);
  // puts("");
  f(i, t1, (int)vis.size() - 1) {
    reg x = vis[i];
    if (cnt + th * dis[x] >= ans) return;
    f(j, t2, (int)v[x].size() - 1) {
      reg y = v[x][j].second, z = v[x][j].first;
      if (in[y]) continue;
      in[y] = 1;
      vis.push_back(y);
      dis[y] = dis[x] + 1;
      th -= v[y][0].first;
      dfs(cnt + z * dis[y], num + 1, i, j + 1);
      th += v[y][0].first;
      dis[y] = 0;
      vis.pop_back();
      in[y] = 0;
    }
    t2 = 0;
  }
  if (num >= N) {
    ans = min(ans, cnt);
    return;
  }
}

int main() {
  scanf("%d%d", &N, &M);
  if (M == 0) {
    puts("0");
    return 0;
  }
  ms(g, 0x7f);
  f(i, 1, M) {
    reg u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u][v] = g[v][u] = min(g[u][v], w);
  }
  f(i, 1, N) f(j, 1, N) if (g[i][j] < INF) v[i].push_back(mp(g[i][j], j));
  f(i, 1, N) sort(v[i].begin(), v[i].end()), th += v[i][0].first;
  // f(i, 1, N) {
  //   f(j, 0, (int)v[i].size() - 1)
  //       printf("(%d, %d) ", v[i][j].first, v[i][j].second);
  //   puts("");
  // }
  // printf("%d\n", th);
  ans = INF;
  f(i, 1, N) {
    in[i] = 1;
    th -= v[i][0].first;
    vis.push_back(i);
    dfs(0, 1, 0, 0);
    vis.pop_back();
    th += v[i][0].first;
    in[i] = 0;
  }
  printf("%d\n", ans);
}
