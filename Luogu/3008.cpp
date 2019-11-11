#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define mp(a, b) make_pair(a, b)
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;

const int SIZE = 25006, INF = 0x3f3f3f3f;
int T, R, P, S, tot, deg[SIZE], c[SIZE], d[SIZE];
bool b[SIZE];
vector<pair<int, int> > v[SIZE];
vector<int> block[SIZE];

void dfs(int x) {
  f(i, 0, (int)v[x].size() - 1) {
    const reg &y = v[x][i].first;
    if (c[y]) continue;
    c[y] = tot;
    block[tot].push_back(y);
    dfs(y);
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%d%d%d%d", &T, &R, &P, &S);
  f(i, 1, R) {
    reg a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    v[a].push_back(mp(b, c));
    v[b].push_back(mp(a, c));
  }
  f(i, 1, T) if (!c[i]) c[i]=++tot, dfs(i);
  f(i, 1, P) {
    reg a, b, tc;
    scanf("%d%d%d", &a, &b, &tc);
    v[a].push_back(mp(b, tc));
    deg[c[b]]++;
  }
  queue<int> q;
  q.push(c[S]);
  f(i, 1, tot) if (deg[i] == 0) q.push(i);
  ms(d, 0x7f);
  d[S] = 0;
  while (q.size()) {
    reg x = q.front();
    q.pop();
    priority_queue<pair<int, int> > pq;
    f(i, 1, T) if (c[i]==x) pq.push(mp(-d[i], i));
    while (pq.size()) {
      reg y = pq.top().second;
      pq.pop();
      if (b[y]) continue;
      b[y] = 1;
      f(i, 0, (int)v[y].size() - 1) {
        const reg &j = v[y][i].first;
        if (c[j] != c[y] && --deg[c[j]] == 0) q.push(c[j]);
        if (d[y] + v[y][i].second >= d[j]) continue;
        d[j] = d[y] + v[y][i].second;
        if (c[j] == c[y]) pq.push(mp(-d[j], j));
      }
    }
  }
  f(i, 1, T) d[i] > INF ? puts("NO PATH") : printf("%d\n", d[i]);
}