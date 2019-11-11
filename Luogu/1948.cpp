#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define SIZE 1006
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

int N, P, K, d[SIZE], ml = -1;
bool b[SIZE];
vector<pair<int, int> > v[SIZE];

inline int bfs(const int &lim) {
  memset(d, 0x3f, sizeof(d));
  memset(b, 0, sizeof(b));
  // printf("\n%d\n", lim);
  deque<int> dq;
  dq.push_back(1), d[1] = 0;
  while (dq.size()) {
    reg x = dq.front();
    dq.pop_front();
    if (b[x]) continue;
    b[x] = true;
    // printf("!%d\n", x);
    f(i, 0, (int)v[x].size() - 1) {
      const reg &y = v[x][i].first, e = v[x][i].second;
      // printf("   %d\n", y);
      if (b[y]) continue;
      if (e > lim) {
        if (d[y] <= d[x] + 1) continue;
        d[y] = d[x] + 1;
        dq.push_back(y);
      } else {
        if (d[y] <= d[x]) continue;
        d[y] = d[x];
        dq.push_front(y);
      }
    }
  }
  return d[N];
}

int main() {
  scanf("%d%d%d", &N, &P, &K);
  f(i, 1, P) {
    reg a, b, l;
    scanf("%d%d%d", &a, &b, &l);
    v[b].push_back(make_pair(a, l));
    v[a].push_back(make_pair(b, l));
    ml = max(ml, l);
  }
  if (bfs(ml) > K) {
    puts("-1");
    return 0;
  }
  reg l = 0, r = ml;
  while (l < r) {
    reg mid = (l + r) >> 1;
    if (bfs(mid) <= K)
      r = mid;
    else
      l = mid + 1;
  }
  printf("%d\n", r);
}
