#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;
#define f(i, s, t) for (int i = s; i != t + 1; i++)

const int size = 5e5 + 10;
int n, m, cnt, s[size], len[size], d[size], fa[size][21], bel[size], id[size],
    du[size];
int tot, head[size], ver[size * 2], Next[size * 2];
queue<int> q;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = getchar();
  }
  return x * f;
}
inline bool cmp(int x1, int y1, int x2, int y2) {
  if (max(x1, y1) != max(x2, y2)) return max(x1, y1) < max(x2, y2);
  if (min(x1, y1) != min(x2, y2)) return min(x1, y1) < min(x2, y2);
  return x1 >= y1;
}
inline void add(int x, int y) {
  ver[++tot] = y;
  Next[tot] = head[x];
  head[x] = tot;
}
inline int lca(int x, int y) {
  if (d[x] > d[y]) swap(x, y);
  for (int i = 20; ~i; i--) {
    if (d[fa[y][i]] >= d[x]) y = fa[y][i];
  }
  if (x == y) return x;
  for (int i = 20; ~i; i--) {
    if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  }
  return fa[x][0];
}
int main() {
  n = read();
  m = read();
  for (int i = 1; i <= n; i++) fa[i][0] = read(), du[fa[i][0]]++;
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 1; i <= n; i++) {
      fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
  }
  for (int i = 1; i <= n; i++)
    if (!du[i]) q.push(i);
  while (q.size()) {
    int x = q.front();
    q.pop();
    if ((--du[fa[x][0]]) == 0) q.push(fa[x][0]);
  }
  for (int i = 1; i <= n; i++) {
    if (du[i] && !bel[i]) {
      int j;
      for (j = i, ++cnt; !bel[j]; j = fa[j][0]) {
        bel[j] = cnt;
        s[j] = ++len[cnt];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (bel[i])
      d[i] = 0, id[i] = i, q.push(i);
    else
      add(fa[i][0], i);
  }
  while (q.size()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = Next[i]) {
      int y = ver[i];
      d[y] = d[x] + 1;
      id[y] = id[x];
      q.push(y);
    }
  }
  f(i, 1, n) printf("%d ", du[i]); puts("");
  f(i, 1, n) printf("%d ", bel[i]); puts("");
  f(i, 1, n) printf("%d ", id[i]); puts("");
  for (int i = 1; i <= m; i++) {
    int a = read(), b = read();
    if (bel[id[a]] != bel[id[b]])
      printf("-1 -1\n");
    else if (id[a] == id[b]) {
      int p = lca(a, b);
      printf("%d %d\n", d[a] - d[p], d[b] - d[p]);
    } else {
      int x1 = d[a] + (s[id[b]] - s[id[a]] + len[bel[id[a]]]) % len[bel[id[a]]],
          y1 = d[b];
      int x2 = d[a],
          y2 = d[b] + (s[id[a]] - s[id[b]] + len[bel[id[b]]]) % len[bel[id[b]]];
      if (cmp(x1, y1, x2, y2))
        printf("%d %d\n", x1, y1);
      else
        printf("%d %d\n", x2, y2);
    }
  }
  return 0;
}