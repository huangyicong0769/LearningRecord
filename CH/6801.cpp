#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t; i++)

const int SN = 106, d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int N, M, T, f[SN * SN];
bool b[SN][SN], v[SN * SN];
vector<int> e[SN * SN];

bool dfs(const int &x) {
  f(i, 0, e[x].size()) {
    const reg &y = e[x][i];
    if (v[y]) continue;
    v[y] = 1;
    if (f[y] == -1 || dfs(f[y])) {
      f[y] = x;
      return true;
    }
  }
  return false;
}

int main() {
  scanf("%d%d", &N, &T);
  f(i, 0, T) {
    reg x, y;
    scanf("%d%d", &x, &y);
    b[x - 1][y - 1] = 1;
  }
  f(x, 0, N) f(y, 0, N) if (!b[x][y]) f(k, 0, 4) {
    reg nx = x + d[k][0], ny = y + d[k][1];
    if (nx >= 0 && nx < N && ny >= 0 && ny < N && !b[nx][ny])
      e[x * N + y].push_back(nx * N + ny), e[nx * N + ny].push_back(x * N + y);
  }
  memset(f, -1, sizeof(f));
  reg ans = 0;
  f(i, 0, N) f(j, 0, N) if (((i ^ j) & 1) == 0) {
    memset(v, 0, sizeof(v));
    if (dfs(i * N + j)) ans++;
  }
  printf("%d\n", ans);
}