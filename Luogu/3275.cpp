#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define ll long long
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define mp(a, b) make_pair(a, b)
using namespace std;

const int SI = 100006;
int N, K, scc, num, top, dfn[SI], low[SI], c[SI], stack[SI], d[SI], deg[SI],
    sum[SI];
bool ins[SI];
vector<pair<int, int> > e[SI], ec[SI];

inline void add(int x, int y, int z) { e[x].push_back(make_pair(y, z)); }

inline void addc(int x, int y, int z) {
  ec[x].push_back(make_pair(y, z));
  ++deg[y];
}

void tarjan(int x) {
  // cout << "tarjan " << x << endl;
  dfn[x] = low[x] = ++num;
  stack[++top] = x, ins[x] = 1;
  f(i, 0, (int)e[x].size() - 1) {
    const reg &y = e[x][i].first;
    // cout << "tar " << x << ' ' << i << endl;
    if (!dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (ins[y])
      low[x] = min(low[x], dfn[y]);
  }
  // cout << "tarjan, pop stack " << x << endl;
  if (low[x] == dfn[x]) {
    ++scc;
    reg y;
    do {
      y = stack[top--], sum[scc]++, c[y] = scc, ins[y] = 0;
    } while (x != y);
  }
}

il ll topsort() {
  queue<int> q;
  for (int i = 1; i <= scc; i++)
    if (!deg[i]) q.push(i);
  while (q.size()) {
    int x = q.front();
    q.pop();
    f(i, 0, (int)ec[x].size() - 1) {
      const reg &y = ec[x][i].first, &z = ec[x][i].second;
      d[y] = max(d[y], d[x] + z);
      if (!--deg[y]) q.push(y);
    }
  }
  // cout << "4" << endl;
  ll ans = 0;
  f(i, 1, scc) ans += (ll)d[i] * sum[i];
  return ans;
}

int main() {
  // cout << "0" << endl;
  scanf("%d%d", &N, &K);
  f(i, 1, K) {
    reg x, a, b;
    scanf("%d%d%d", &x, &a, &b);
    if (x == 1 || x == 3) e[b].push_back(mp(a, 0));
    if (x == 1 || x == 5) e[a].push_back(mp(b, 0));
    if (x == 2) e[a].push_back(mp(b, 1));
    if (x == 4) e[b].push_back(mp(a, 1));
  }
  // cout << "0.1" << endl;
  f(i, 1, N) e[0].push_back(mp(i, 1));
  // cout << "1" << endl;
  tarjan(0);
  // cout << "2" << endl;
  // f(i, 1, N) printf("%d ", c[i]); puts("");
  f(x, 0, N) f(i, 0, (int)e[x].size() - 1) {
    const reg &y = e[x][i].first, &z = e[x][i].second;
    if (c[x] != c[y])
      ec[c[x]].push_back(mp(c[y], z)), ++deg[c[y]];
    else if (z) {
      // printf("%d %d %d %d %d\n", x, y, );
      puts("-1");
      return 0;
    }
  }
  // cout << "3" << endl;
  printf("%lld\n", topsort());
}