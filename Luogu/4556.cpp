#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#define il inline
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

const int SIZE = 100006;
int N, M, T, tot, fa[SIZE][18], lca[SIZE], d[SIZE], root[SIZE], ans[SIZE];
vector<int> v[SIZE];

struct STNode {
  int lc, rc, dat1, dat2;
} tr[SIZE * 18 * 4];

il void preWork() {
  queue<int> q;
  q.push(1);
  d[1] = 1;
  while (q.size()) {
    int x = q.front();
    q.pop();
    f(i, 0, (int)v[x].size() - 1) {
      int y = v[x][i];
      if (d[y]) continue;
      d[y] = d[x] + 1;
      fa[y][0] = x;
      for (int j = 1; j <= T; j++) fa[y][j] = fa[fa[y][j - 1]][j - 1];
      q.push(y);
    }
  }
}

il int LCA(int x, int y) {
  if (d[x] < d[y]) swap(x, y);
  for (reg i = T; i >= 0; i--)
    if (d[fa[x][i]] >= d[y]) x = fa[x][i];
  if (x == y) return y;
  for (reg i = T; i >= 0; i--)
    if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

void insert(int p, int l, int r, int val, int del) {
  if (l == r) {
    tr[p].dat1 += del;
    tr[p].dat2 = tr[p].dat1 ? l : 0;
    return;
  }
  reg mid = (l + r) >> 1;
  if (val <= mid) {
    if (tr[p].lc == 0) tr[p].lc = ++tot;
    insert(tr[p].lc, l, mid, val, del);
  } else {
    if (tr[p].rc == 0) tr[p].rc = ++tot;
    insert(tr[p].rc, mid + 1, r, val, del);
  }
  tr[p].dat1 = max(tr[tr[p].lc].dat1, tr[tr[p].rc].dat1);
  tr[p].dat2 = tr[tr[p].lc].dat1 >= tr[tr[p].rc].dat1 ? tr[tr[p].lc].dat2
                                                      : tr[tr[p].rc].dat2;
}

int merge(int p, int q, int l, int r) {
  if (p == 0) return q;
  if (q == 0) return p;
  if (l == r) {
    tr[p].dat1 += tr[q].dat1;
    tr[p].dat2 = tr[p].dat1 ? l : 0;
    return p;
  }
  reg mid = (l + r) >> 1;
  tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid);
  tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);
  tr[p].dat1 = max(tr[tr[p].lc].dat1, tr[tr[p].rc].dat1);
  tr[p].dat2 = tr[tr[p].lc].dat1 >= tr[tr[p].rc].dat1 ? tr[tr[p].lc].dat2
                                                      : tr[tr[p].rc].dat2;
  return p;
}

void dfs(int x) {
  f(i, 0, (int)v[x].size() - 1) {
    reg y = v[x][i];
    if (y == fa[x][0]) continue;
    dfs(y);
    root[x] = merge(root[x], root[y], 1, 100000);
  }
  ans[x] = tr[root[x]].dat2;
}

int main() {
  scanf("%d%d", &N, &M);
  T = (int)(log(N) / log(2)) + 1;
  f(i, 2, N) {
    reg a, b;
    scanf("%d%d", &a, &b);
    v[a].push_back(b), v[b].push_back(a);
  }
  preWork();
  f(i, 1, N) root[i] = ++tot;
  f(i, 1, M) {
    reg x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    reg t = LCA(x, y);
    insert(root[x], 1, 100000, z, 1);
    insert(root[y], 1, 100000, z, 1);
    insert(root[t], 1, 100000, z, -1);
    if (fa[t][0]) insert(root[fa[t][0]], 1, 100000, z, -1);
  }
  dfs(1);
  f(i, 1, N) printf("%d\n", ans[i]);
}