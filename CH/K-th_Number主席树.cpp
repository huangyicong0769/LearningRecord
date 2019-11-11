// ykhoj P3358
// POJ 2104
// SPOJ 3946
// luohu SP3946
#include <algorithm>
#include <cstdio>
#include <iostream>
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
using namespace std;
const int SIZE = 200006;

struct SegmentTreeNode {
  int l, r, cnt;
} st[SIZE * 20];
int N, M, t, tot, root[SIZE], a[SIZE], b[SIZE];

int Build(int l, int r) {
  int p = ++tot;
  st[p].cnt = 0;
  if (l == r) return p;
  int mid = (l + r) >> 1;
  st[p].l = Build(l, mid);
  st[p].r = Build(mid + 1, r);
  return p;
}

int Insert(int p, int l, int r, int x) {
  int q = ++tot;
  st[q] = st[p];
  if (l == r) {
    st[q].cnt++;
    return q;
  }
  int mid = (l + r) >> 1;
  if (x <= mid)
    st[q].l = Insert(st[p].l, l, mid, x);
  else
    st[q].r = Insert(st[p].r, mid + 1, r, x);
  st[q].cnt = st[st[q].l].cnt + st[st[q].r].cnt;
  return q;
}

int Ask(int p, int q, int l, int r, int x) {
  if (l == r) return l;
  int mid = (l + r) >> 1, tmp = st[st[p].l].cnt - st[st[q].l].cnt;
  if (x <= tmp)
    return Ask(st[p].l, st[q].l, l, mid, x);
  else
    return Ask(st[p].r, st[q].r, mid + 1, r, x - tmp);
}

int main() {
  scanf("%d%d", &N, &M);
  f(i, 1, N) {
    scanf("%d", &a[i]);
    b[++t] = a[i];
  }
  sort(b + 1, b + t + 1);
  t = unique(b + 1, b + 1 + t) - (b + 1);
  root[0] = Build(1, t);
  f(i, 1, N) {
    int x = lower_bound(b + 1, b + 1 + t, a[i]) - b;
    root[i] = Insert(root[i - 1], 1, t, x);
  }
  f(i, 1, M) {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    int ans = Ask(root[r], root[l - 1], 1, t, x);
    printf("%d\n", b[ans]);
  }
}