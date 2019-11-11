#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define N 300005
#define int long long

int root[N];
int n, m, T, tot;
int ch[N * 20][2];
int l[N * 20], r[N * 20];
int sze[N * 20], prio[N * 20];

int newnode(int x, int y) {
  tot++;
  l[tot] = x;
  r[tot] = y;
  sze[tot] = y - x + 1;
  prio[tot] = rand();
  return tot;
}

void pushup(int x) { sze[x] = sze[ch[x][0]] + sze[ch[x][1]] + r[x] - l[x] + 1; }

int merge(int x, int y) {
  if (!x or !y) return x + y;
  if (prio[x] < prio[y]) {
    ch[x][1] = merge(ch[x][1], y);
    pushup(x);
    return x;
  } else {
    ch[y][0] = merge(x, ch[y][0]);
    pushup(y);
    return y;
  }
}

void split_new(int now, int k) {  //把now的大小变为k
  if (k >= r[now] - l[now] + 1) return;
  int want = l[now] + k - 1;
  int nn = newnode(want + 1, r[now]);
  r[now] = want;
  ch[now][1] = merge(nn, ch[now][1]);
  pushup(now);
}

void split(int now, int k, int &x, int &y) {
  if (!now)
    x = y = 0;
  else {
    if (sze[ch[now][0]] >= k) {
      y = now;
      split(ch[now][0], k, x, ch[now][0]);
    } else {
      split_new(now, k - sze[ch[now][0]]);
      x = now;
      split(ch[now][1], k - sze[ch[now][0]] - (r[now] - l[now] + 1), ch[now][1],
            y);
    }
    pushup(now);
  }
}

signed main() {
  srand(time(0));
  scanf("%lld%lld%lld", &n, &m, &T);
  for (int i = 1; i <= n; i++) root[i] = newnode((i - 1) * m + 1, i * m - 1);
  for (int i = 1; i <= n; i++)
    root[n + 1] = merge(root[n + 1], newnode(i * m, i * m));
  while (T--) {
    int a, b;
    scanf("%lld%lld", &a, &b);
    if (b != m) {
      int x, y, z;
      split(root[a], b, x, y);
      split(x, b - 1, x, z);
      printf("%lld\n", l[z]);
      int r4, r5, r6;
      split(root[n + 1], a, r4, r5);
      split(r4, a - 1, r4, r6);
      root[a] = merge(x, merge(y, r6));
      root[n + 1] = merge(r4, merge(r5, z));
    } else {
      int x, y, z;
      split(root[n + 1], a, x, y);
      split(x, a - 1, x, z);
      printf("%lld\n", l[z]);
      root[n + 1] = merge(x, merge(y, z));
    }
  }
  return 0;
}