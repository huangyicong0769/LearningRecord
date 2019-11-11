#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 106, inf = 0x3f3f3f3f;
int N, M, d[SN][SN];
double edge[SN][SN], ans[SN];

int main() {
  ms(d, 0x3f);
  scanf("%d%d", &N, &M);
  f(i, 1, M) {
    reg a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    d[a][b] = d[b][a] = c;
    edge[a][b] = edge[b][a] = 1;
  }
  f(k, 1, N) f(i, 1, N) f(j, 1, N){
    if (d[i][j] > d[i][k] + d[k][j]) {
      d[i][j] = d[i][k] + d[k][j], edge[i][j] = edge[i][k] * edge[k][j];
      continue;
    }
    if (d[i][j] == d[i][k] + d[k][j]) edge[i][j] += edge[i][k] * edge[k][j];
  }
  f(i, 1, N) f(s, 1, N)
      f(t, 1, N) if (i != s && i != t && s != t && d[s][t] == d[s][i] + d[i][t])
          ans[i] += edge[s][i] * edge[i][t] / edge[s][t];
  f(i, 1, N) printf("%.3lf\n", ans[i]);
}