#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline

const int SN = 506, SM = SN * SN;
int S, P, x[SN], y[SN], c[SN];
struct Edge {
  int x, y;
  double w;
  bool operator<(Edge b) const { return w < b.w; }
} e[SM];

int get(int x) { return c[x] == x ? x : c[x] = get(c[x]); }

il double dist(int a, int b) {
  return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

int main() {
  cin >> S;
  while (cin >> S >> P) {
    f(i, 1, P) c[i] = i, scanf("%d%d", &x[i], &y[i]);
    reg tot = 0;
    f(i, 1, P) f(j, i + 1, P) e[++tot].x = i, e[tot].y = j,
                              e[tot].w = dist(i, j);
    sort(e + 1, e + 1 + tot);
    reg cnt = 0;
    f(i, 1, tot) {
      reg x = get(e[i].x), y = get(e[i].y);
      if (x == y) continue;
      c[x] = y;
      if (++cnt == P - S) {
        printf("%.2lf\n", e[i].w);
        break;
      }
    }
  }
}