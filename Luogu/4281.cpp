#include <bits/stdc++.h>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline

const int SN = 500006;
int N, M, tot, Head[SN], Next[SN << 1], Ver[SN << 1], fa[SN << 1][20], d[SN];

il void add(int x, int y) {
  Ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
il void preWork() {
  queue<int> q;
  q.push(1);
  d[1] = 1;
  while (q.size()) {
    reg x = q.front();
    q.pop();
    for (reg i = Head[x]; i; i = Next[i]) {
      if (d[Ver[i]]) continue;
      d[Ver[i]] = d[x] + 1;
      fa[Ver[i]][0] = x;
      f(j, 1, 19) fa[Ver[i]][j] = fa[fa[Ver[i]][j - 1]][j - 1];
      q.push(Ver[i]);
    }
  }
}
il int LCA(int x, int y) {
  if (d[x] < d[y]) swap(x, y);
  for (reg j = 19; j >= 0; j--)
    if (d[fa[x][j]] >= d[y]) x = fa[x][j];
  if (x == y) return x;
  for (reg j = 19; j >= 0; j--)
    if (fa[x][j] != fa[y][j]) x = fa[x][j], y = fa[y][j];
  return fa[x][0];
}

int main() {
  scanf("%d%d", &N, &M);
  f(i, 2, N) {
    reg u, v;
    scanf("%d%d", &u, &v);
    add(u, v), add(v, u);
  }
  preWork();
  f(i, 1, M) {
    reg A, B, C;
    scanf("%d%d%d", &A, &B, &C);
    reg a = LCA(A, B), b = LCA(A, C), c = LCA(B, C);
    reg ans = 0;
    if (a==b) ans=c;
    else if (a==c) ans=b;
    else ans=a;
    printf("%d %d\n", ans, d[A] + d[B] + d[C] - d[a] - d[b] - d[c]);
  }
}