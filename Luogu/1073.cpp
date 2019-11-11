#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define SIZE 100006
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

int N, M, pr[SIZE], d[SIZE], f[SIZE];
bool b[SIZE];
vector<int> v1[SIZE], v2[SIZE];

int main() {
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  scanf("%d%d", &N, &M);
  f(i, 1, N) scanf("%d", &pr[i]);
  f(i, 1, M) {
    reg a, b, s;
    scanf("%d%d%d", &a, &b, &s);
    v1[a].push_back(b), v2[b].push_back(a);
    if (s == 2) v1[b].push_back(a), v2[a].push_back(b);
  }
  memset(d, 0x3f, sizeof(d));
  b[1] = 1, d[1] = pr[1];
  priority_queue<pair<int, int> > pq;
  f(i, 0, (int)v1[1].size() - 1) d[v1[1][i]] = min(d[1], pr[v1[1][i]]);
  f(i, 1, N) pq.push(make_pair(-d[i], i));
  while (pq.size()) {
    reg j = pq.top().second;
    pq.pop();
    b[j] = 1;
    f(k, 0, (int)v1[j].size() - 1) {
      const reg &y = v1[j][k];
      if (d[y] <= d[j]) continue;
      d[y] = min(d[j], pr[y]);
      pq.push(make_pair(-d[y], y));
    }
  }
  memset(b, 0, sizeof(b));
  memset(f, 0xcf, sizeof(f));
  b[N] = 1, f[N] = pr[N];
  while (pq.size()) pq.pop();
  f(i, 0, (int)v2[N].size() - 1) f[v2[N][i]] = max(f[N], pr[v2[N][i]]);
  f(i, 1, N) pq.push(make_pair(f[i], i));
  while (pq.size()) {
    reg j = pq.top().second;
    pq.pop();
    if (b[j]) continue;
    b[j] = 1;
    f(k, 0, (int)v2[j].size() - 1) {
      const reg &y = v2[j][k];
      if (f[y] >= f[j]) continue;
      f[y] = max(f[j], pr[y]);
      pq.push(make_pair(f[y], y));
    }
  }
  reg ans = 0;
  f(i, 1, N) ans = max(ans, f[i] - d[i]);
  printf("%d\n", ans);
}