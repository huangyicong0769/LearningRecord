#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define SIZE 12006
#define reg register
#define il inline
#define f(i, s, t, d) for (reg int i = s; i != t; i += d)
using namespace std;

int N, M, tot, trie[SIZE * 32][2], root[SIZE], id[SIZE * 32], a[SIZE],
    f[100][SIZE];

il void add(int pre, int val, int i) {
  reg int p = root[i] = ++tot;
  id[p] = i;
  f(k, 30, -1, -1) {
    reg int j = (val >> k) & 1;
    trie[p][j ^ 1] = trie[pre][j ^ 1];
    p = trie[p][j] = ++tot;
    pre = trie[pre][j];
    id[p] = i;
  }
}
il int ask(int l, int r, int val) {
  reg int ans = 0, p = root[r];
  f(k, 30, -1, -1) {
    reg int j = ((val >> k) & 1) ^ 1;
    if (id[trie[p][j]] > l) ans |= 1 << k;
    else j ^= 1;
    p = trie[p][j];
  }
  return ans;
}

int main() {
  memset(id, -1, sizeof(id));
  scanf("%d%d", &N, &M);
  f(i, 1, N+1, 1) scanf("%d", &a[i]), a[i] ^= a[i - 1];
  int t = sqrt(M), len = N / t;
  if (N % t) len++;
  add(0, 0, 0);
  f(i, 1, N+1, 1) add(root[i - 1], a[i], i);
  f(i, 0, t, 1) f(j, i * len + 1, N+1, 1) f[i][j] =
      max(f[i][j-1], ask(i * len, j - 1, a[j]));
  int ans = 0;
  f(i, 1, M+1, 1) {
    int x, y;
    scanf("%d%d", &x, &y);
    x = (x + ans) % N + 1, y = (y + ans) % N + 1;
    if (x > y) swap(x, y);
    reg int p = --x / len;
    if (x % len) p++;
    ans = p * len < y ? f[p][y] : 0;
    f(j, x, min(p * len, y)+1, 1) ans = max(ans, ask(x, y, a[j]));
    printf("%d\n", ans);
    ans %= N;
  }
}