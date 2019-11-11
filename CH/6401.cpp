#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;

const int SIZE = 1000006;
int N, t, q[SIZE], s[SIZE][2], c[SIZE], f[SIZE][2], fa[SIZE];
vector<int> v[SIZE];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

void dp(int x, const int &sp) {
  reg num = 0x7fffffff;
  f[x][0] = 0;
  f(i, 0, (int)v[x].size() - 1) {
    if (sp != v[x][i]) dp(v[x][i], sp);
    f[x][0] += max(f[v[x][i]][1], f[v[x][i]][0]);
    num = min(num, max(f[v[x][i]][1], f[v[x][i]][0]) - f[v[x][i]][0]);
  }
  f[x][1] = f[x][0] - num + 1;
}

int main() {
  scanf("%d", &N);
  f(i, 1, N) fa[i] = i;
  f(i, 1, N) {
    reg x;
    scanf("%d", &x);
    reg p = getfa(x), q = getfa(i);
    if (p == q) {
      s[++t][0] = x;
      s[t][1] = i;
    } else {
      v[x].push_back(i);
      fa[q] = p;
    }
  }
  reg ans = 0;
  f(i, 1, t) {
    dp(s[i][0], 0);
    dp(s[i][1], s[i][0]);
    reg num = f[s[i][1]][1];
    f[s[i][0]][1] = f[s[i][0]][0] + 1;
    dp(s[i][1], s[i][0]);
    ans += max(num, f[s[i][1]][0]);
  }
  printf("%d\n", ans);
}