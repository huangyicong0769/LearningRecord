#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline

const int SN = 500006;
int N, K, cnt, fa[SN][20], du[SN], d[SN], s[SN], len[SN], id[SN], cp[SN];
int tot, Head[SN], Ver[SN], Next[SN];  // opt gra

il void add(int a, int b) {
  Ver[++tot] = b, Next[tot] = Head[a], Head[a] = tot;
}

il void topsort() {
  queue<int> q;
  f(i, 1, N) if (!du[i]) q.push(i);
  for (; q.size();) {
    reg x = q.front();
    q.pop();
    if ((--du[fa[x][0]]) == 0) q.push(fa[x][0]);
  }
  f(x, 1, N) if (du[x] && !cp[x]) {
    cnt++;
    for (reg i = x; !cp[i]; i = fa[i][0]) cp[i] = cnt, s[i] = ++len[cnt];
  }
}

il void preWork() {
  f(j, 1, 19) f(i, 1, N) fa[i][j] = fa[fa[i][j - 1]][j - 1];
  topsort();
  queue<int> q;
  f(i, 1, N) if (cp[i]) d[i] = 0, id[i] = i, q.push(i);
  else add(fa[i][0], i);
  while (q.size()) {
    reg x = q.front();
    q.pop();
    for (reg i = Head[x]; i; i = Next[i])
      d[Ver[i]] = d[x] + 1, id[Ver[i]] = id[x], cp[Ver[i]] = cp[x],
      q.push(Ver[i]);
  }
}

il int lca(int x, int y) {
  if (d[x] < d[y]) swap(x, y);
  for (reg j = 19; j >= 0; j--)
    if (d[fa[x][j]] >= d[y]) x = fa[x][j];
  if (x == y) return x;
  for (reg j = 19; j >= 0; j--)
    if (fa[x][j] != fa[y][j]) x = fa[x][j], y = fa[y][j];
  return fa[x][0];
}

il bool cmp(int x1, int y1, int x2, int y2) {
  if (max(x1, y1) != max(x2, y2)) return max(x1, y1) < max(x2, y2);
  if (min(x1, y1) != min(x2, y2)) return min(x1, y1) < min(x2, y2);
  return x1 >= y1;
}

int main() {
  scanf("%d%d", &N, &K);
  f(i, 1, N) scanf("%d", &fa[i][0]), du[fa[i][0]]++;
  preWork();
  f(i, 1, K) {
    reg a, b;
    scanf("%d%d", &a, &b);
    if (cp[a] != cp[b])
      puts("-1 -1");
    else if (id[a] == id[b]) {
      reg p = lca(a, b);
      printf("%d %d\n", d[a] - d[p], d[b] - d[p]);
    } else {
      reg x1 = d[a] + (s[id[b]] - s[id[a]] + len[cp[a]]) % len[cp[a]],
          y1 = d[b], x2 = d[a],
          y2 = d[b] + (s[id[a]] - s[id[b]] + len[cp[b]]) % len[cp[b]];
      cmp(x1, y1, x2, y2) ? printf("%d %d\n", x1, y1)
                          : printf("%d %d\n", x2, y2);
    }
  }
}
 