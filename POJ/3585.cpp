#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define SIZE 200006
#define reg register
#define f(i, s, t) for (reg int i = s; i < t; i++)
using namespace std;

int T, N, d[SIZE], f[SIZE];
vector<int> v1[SIZE], v2[SIZE];
bool b[SIZE];

void dp(int x) {
  b[x] = 1;
  f(i, 0, v1[x].size()) {
    const int &y = v1[x][i];
    if (b[y]) continue;
    dp(y);
    if (v1[y].size() == 1) d[x] += v2[x][i];
    else d[x] += min(d[y], v2[x][i]);
  }
}

void dfs(int x) {
  b[x] = 1;
  f(i, 0, v1[x].size()) {
    const int &y = v1[x][i];
    if (b[y]) continue;
    if (v1[x].size() == 1) f[y] = d[y] + v2[x][i];
    else f[y] = d[y] + min(f[x] - min(v2[x][i], d[y]), v2[x][i]);
    dfs(y);
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    memset(d, 0, sizeof(d));
    memset(f, 0, sizeof(f));
    scanf("%d", &N);
    f(i, 1, N) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      v1[x].push_back(y), v2[x].push_back(z);
      v1[y].push_back(x), v2[y].push_back(z);
    }
    memset(b, 0, sizeof(b));
    dp(1);
    memset(b, 0, sizeof(b));
    f[1]=d[1];
    dfs(1);
    reg int ans = 0;
    f(i, 1, N + 1) ans = max(ans, f[i]);
    printf("%d\n", ans);
    f(i, 1, N + 1) v1[i].clear(), v2[i].clear();
  }
}