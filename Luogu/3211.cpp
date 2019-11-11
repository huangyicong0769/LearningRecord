#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define SIZE 106
#define rg register
#define reg rg int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

int N, M;
double a[SIZE][SIZE];
vector<int> v1[SIZE], v2[SIZE];

int main() {
  scanf("%d%d", &N, &M);
  f(i, 1, M) {
    reg u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    v1[u].push_back(v), v2[u].push_back(w);
    if (u != v) v1[v].push_back(u), v2[v].push_back(w);
  }
  rg double ans = 0.0;
  f(k, 0, 30) {
    memset(a, 0, sizeof(a));
    f(i, 1, N-1) {
      a[i][i] = v1[i].size();
      f(j, 0, (int)v1[i].size() - 1) {
        const reg &y = v1[i][j];
        if (v2[i][j] >> k & 1)
          a[i][y] += 1.0, a[i][N + 1]++;
        else
          a[i][y] += -1.0;
      }
    }
    a[N][N]=v1[N].size();
    f(i, 1, N - 1) {
      reg k = i;
      f(j, i + 1, N - 1) if (fabs(a[j][i]) > fabs(a[k][i])) k = j;
      f(j, 1, N + 1) swap(a[i][j], a[k][j]);
      f(j, i + 1, N) {
        rg double r = a[j][i] / a[i][i];
        f(t, 1, N + 1) a[j][t] -= r * a[i][t];
      }
    }
    for (reg i = N; i > 0; i--) {
      f(j, i + 1, N) a[i][N + 1] -= a[i][j] * a[j][0];
      a[i][0] = a[i][N + 1] / a[i][i];
    }
    ans += (1 << k) * a[1][0];
  }
  printf("%.3lf\n", ans);
}