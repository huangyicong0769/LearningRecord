#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define ms(a, b) memset(a, b, sizeof(a))
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SIZE = 6006;
int T, N, fa[SIZE], si[SIZE];
struct Edge {
  int x, y, z;
  bool operator<(const Edge& a) const { return z < a.z; }
} edge[SIZE];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int main() {
  for (scanf("%d", &T); T; T--) {
    scanf("%d", &N);
    f(i, 1, N - 1) {
      reg x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      edge[i].x = x, edge[i].y = y, edge[i].z = z;
    }
    f(i, 1, N) fa[i] = i, si[i] = 1;
    sort(edge + 1, edge + N);
    reg ans = 0;
    f(i, 1, N - 1) {
      reg x = getfa(edge[i].x), y = getfa(edge[i].y), &z = edge[i].z;
      if (x == y) continue;
      ans += (long long)(z + 1) * (si[x] * si[y] - 1);
      fa[x] = y;
      si[y] += si[x];
    }
    printf("%d\n", ans);
  }
}
