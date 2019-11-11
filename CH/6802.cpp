#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t; i++)

const int SN = 406;
int N, M, T, f[SN];
bool b[SN >> 1][SN >> 1], v[SN];
vector<int> e[SN];

bool dfs(int x) {
  f(i, 0, e[x].size()) {
    const reg &y = e[x][i];
    if (v[y]) continue;
    v[y] = 1;
    if (f[y] == -1 || dfs(f[y])) {
      f[y] = x;
      return 1;
    }
  }
  return 0;
}

int main() {
  scanf("%d%d%d", &N, &M, &T);
  f(i, 0, T) {
    reg x, y;
    scanf("%d%d", &x, &y);
    b[x - 1][y - 1] = 1;
  }
  f(x, 0, N) f(y, 0, M) if (!b[x][y]) e[x].push_back(N+y), e[N+y].push_back(x);
  reg ans = 0;
  memset(f, -1, sizeof(f));
  f(x, 0, N) {
    memset(v, 0, sizeof(v));
    ans += dfs(x);
  }
  printf("%d\n", ans);
}