#include <bits/stdc++.h>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;

const int SN = 1006, SM = 2000010;
int N, M, tot, now, cnt, num, top, low[SN], dfn[SN], Head[SN], v[SN], Next[SM],
    Ver[SM], st[SN], c[SN], ab[SN];
bool label, hate[SN][SN];
vector<int> dcc[SN];

il void add(const int &x, const int &y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void cover(const int &x, int color) {
  c[x] = color;
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (v[y] != now) continue;
    if (c[y] && c[y] == color) {
      label = 1;
      return;
    }
    if (!c[y]) cover(y, 3 - color);
  }
}
void tarjan(const int &x, const int &root) {
  dfn[x] = low[x] = ++num;
  st[++top] = x;
  if (x == root && Head[x] == 0) {
    dcc[++cnt].push_back(x);
    return;
  }
  for (reg i = Head[x]; i; i = Next[i]) {
    const reg &y = Ver[i];
    if (!dfn[y]) {
      tarjan(y, root);
      low[x] = min(low[x], low[y]);
      if (low[y] >= dfn[x]) {
        cnt++;
        reg z;
        do {
          z = st[top--], dcc[cnt].push_back(z);
        } while (z != y);
        dcc[cnt].push_back(x);
      }
    } else
      low[x] = min(low[x], dfn[y]);
  }
}

int main() {
  while (scanf("%d%d", &N, &M) && N) {
    ms(Head, 0), ms(hate, 0), ms(dfn, 0), ms(ab, 0), ms(v, 0);
    tot = 1, num = top = cnt = 0;
    f(i, 1, N) dcc[i].clear();
    f(i, 1, M) {
      reg k1, k2;
      scanf("%d%d", &k1, &k2);
      if (k1 == k2) continue;
      hate[k1][k2] = hate[k2][k1] = 1;
    }
    f(i, 1, N - 1) f(j, i + 1, N) if (!hate[i][j]) add(i, j), add(j, i);
    f(i, 1, N) if (!dfn[i]) tarjan(i, i);
    f(i, 1, cnt) {
      now = i;
      f(j, 0, (int)dcc[i].size() - 1) v[dcc[i][j]] = now, c[dcc[i][j]] = 0;
      label = 0;
      cover(dcc[i][0], 1);
      if (label) f(j, 0, (int)dcc[i].size() - 1) ab[dcc[i][j]] = 1;
    }
    reg ans = 0;
    f(i, 1, N) if (!ab[i]) ans++;
    printf("%d\n", ans);
  }
}