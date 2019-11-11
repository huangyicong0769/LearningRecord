#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define SIZE 306
#define reg register
#define f1(i, s, t) for (reg int i = s; i != t; i++)
#define f2(i, s, t) for (reg int i = s; i != t; i--)
using namespace std;

int N, M, f[SIZE][SIZE], s[SIZE];
vector<int> w[SIZE];

void dp(int x) {
  f[x][0] = 0;
  f1(i, 0, w[x].size()) {
    const int &y = w[x][i];
    dp(y);
    f2(t, M, -1) f2(j, t, -1) if (t - j >= 0) f[x][t] =
        max(f[x][t], f[x][t - j] + f[y][j]);
  }
  if (x) f2(t, M, 0) f[x][t] = f[x][t - 1] + s[x];
}

int main() {
  scanf("%d%d", &N, &M);
  f1(i, 1, N + 1) {
    reg int k;
    scanf("%d%d", &k, &s[i]);
    w[k].push_back(i);
  }
  memset(f, 0xcf, sizeof(f));
  dp(0);
  printf("%d\n", f[0][M]);
} 