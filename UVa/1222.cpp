#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#define prework ss.clear(), ss.str(s);
#define reg register
#define f(i, s, t, d) for (reg int i = s; i != t; i += d)
using namespace std;

const int INF = 0x3f3f3f3f, SIZE = 206;
int N, M, tot, f[SIZE][SIZE], sc[SIZE];
bool fa[SIZE];
map<string, int> d;
vector<int> w[SIZE];

int dp(int x) {
  f(i, 1, N + 1, 1) f[x][i] = INF;
  f[x][0] = 0;
  reg int cnt = 1;
  f(i, 0, w[x].size(), 1) {
    const int &y = w[x][i];
    cnt += dp(y);
    f(t, N, -1, -1) f(j, 0, t + 1, 1) f[x][t] =
        min(f[x][t], f[x][t - j] + f[y][j]);
  }
  f[x][cnt] = min(f[x][cnt], sc[x]);
  return cnt;
}

int main() {
  // freopen("input.txt", "r", stdin);
  stringstream ss;
  string s;
  while (getline(cin, s) && s[0] != '#') {
    d.clear();
    memset(fa, 1, sizeof(fa));
    tot = 0;
    prework ss >> N >> M;
    f(i, 1, N + 1, 1) {
      reg int tmp = 0;
      s.clear();
      getline(cin, s);
      prework ss >> s >> tmp;
      if (d.find(s) == d.end()) d[s] = ++tot;
      reg int x = d[s];
      sc[x] = tmp;
      while (ss >> s) {
        if (d.find(s) == d.end()) d[s] = ++tot;
        reg int y = d[s];
        fa[y] = 0;
        w[x].push_back(y);
      }
    }
    f(i, 1, N + 1, 1) if (fa[i]) w[0].push_back(i);
    sc[0] = INF;
    dp(0);
    reg int ans = INF;
    f(i, M, N + 1, 1) ans = min(ans, f[0][i]);
    printf("%d\n", ans);
    f(i, 0, N+1, 1) w[i].clear();
  }
}