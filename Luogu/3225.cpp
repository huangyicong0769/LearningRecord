#include <bits/stdc++.h>
using namespace std;
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define il inline
typedef unsigned long long ull;

const int SN = 50006;
int T, N, M, num, dccs, root, dfn[SN], low[SN], cnt[SN];
int tot, Head[SN], Ver[SN << 1], Next[SN << 1];
int top, st[SN];
bool cut[SN];
vector<int> dcc[SN];
set<int> ex;

il void add(int a, int b) {
  Ver[++tot] = b, Next[tot] = Head[a], Head[a] = tot;
}
void tarjan(int x) {
  dfn[x] = low[x] = ++num;
  if (x == root && Head[x] == 0 && ex.find(x) != ex.end()) {
    dcc[++dccs].push_back(x);
    return;
  }
  st[++top] = x;
  reg int flag = 0;
  for (reg int i = Head[x]; i; i = Next[i]) {
    reg int y = Ver[i];
    if (!dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
      if (dfn[x] <= low[y]) {
        flag++;
        if (x != root || flag > 1) cut[x] = 1;
        dccs++;
        reg int z;
        do {
          z = st[top--];
          dcc[dccs].push_back(z);
        } while (y != z);
        dcc[dccs].push_back(x);
      }
    } else
      low[x] = min(low[x], dfn[y]);
  }
}

int main() {
  T = 0;
  while (~scanf("%d", &M)) {
    if (!M) break;
    ex.clear(), ms(Head, 0), ms(dfn, 0), ms(low, 0), ms(cut, 0);
    tot = 1, dccs = N = top = 0;
    f(i, 1, M) {
      reg int a, b;
      scanf("%d%d", &a, &b);
      N = max(N, max(a, b));
      ex.insert(a), ex.insert(b);
      add(a, b), add(b, a);
    }
    f(i, 1, N) if (!dfn[i]) root = i, tarjan(i);
    ull ans1 = 0, ans2 = 1;
    f(i, 1, dccs) {
      reg ull cnt = 0;
      for (reg vector<int>::iterator j = dcc[i].begin(); j < dcc[i].end(); j++)
        if (cut[*j]) cnt++;
      if (cnt == 0)
        ans1 += 2, ans2 *= (ull)dcc[i].size() * (dcc[i].size() - 1) / 2;
      if (cnt == 1) ans1++, ans2 *= (ull)(dcc[i].size() - 1);
      dcc[i].clear();
    }
    printf("Case %d: %lld %lld\n", ++T, ans1, ans2);
  }
}