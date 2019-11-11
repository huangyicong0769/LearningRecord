#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))
#define mp(a, b) make_pair(a, b)

const int SN = 50, SM = 10000;
int N, M, top1, top2, ans[SM], deg[SN];
bool vis[10000];
vector<pair<int, int> > edges[SN];
pair<int, int> st[SM];

int main() {
#ifdef DEBUG
  freopen("output.txt", "w", stdout);
#endif  // DEBUG
  while (1) {
    top1 = top2 = 0, ms(deg, 0), ms(vis, 0);
    f(i, 1, SN) edges[i].clear();
    reg x, y, z, s;
    scanf("%d%d", &x, &y);
    if (x == 0) break;
    scanf("%d", &z);
    deg[x]++, deg[y]++;
    s = min(x, y);
    edges[x].push_back(mp(z, y)), edges[y].push_back(mp(z, x));
    while (1) {
      scanf("%d%d", &x, &y);
      if (x == 0) break;
      scanf("%d", &z);
      edges[x].push_back(mp(z, y)), edges[y].push_back(mp(z, x));
      deg[x]++, deg[y]++;
    }
    f(i, 1, SN) if (deg[i] % 2) {
      puts("Round trip does not exist.\n");
      goto a;
    }
    f(i, 1, SN) sort(edges[i].begin(), edges[i].end());
    // f(i, 1, 3) {
    //   printf("#%d:\n", i);
    //   for (auto i : edges[i]) printf(" %d %d\n", i.first, i.second);
    // }
    st[++top1] = mp(0, s);
    while (top1) {
      reg x = st[top1].second, w = st[top1].first;
      auto i = edges[x].begin();
      for (; i != edges[x].end(); i++)
        if (!vis[(*i).first]) break;
      if (i != edges[x].end()) {
        st[++top1] = *i;
        vis[(*i).first] = 1;
      } else {
        top1--;
        ans[++top2] = w;
      }
    }
    for (reg i = top2 - 1; i; i--) printf("%d ", ans[i]);
    puts("\n");
  a:;
  }
}