#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline
#define a first
#define b second

const int SN = 50006;
int N, c[SN];
pair<int, int> p[SN];

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il void modify(int x, int y) {
  for (; x <= 2 * N; x += x & -x) c[x] += y;
}

il int query(int x) {
  reg ans = 0;
  for (; x ; x -= x & -x) ans += c[x];
  return ans;
}

int main() {
  N = read();
  f(i, 1, 2 * N) {
    reg x = read();
    if (!p[x].a) p[x].a = i;
    else p[x].b = i;
  }
  sort(p + 1, p + 1 + N);
  reg ans = 0;
  f(i, 1, N) ans += query(p[i].b - 1) - query(p[i].a), modify(p[i].b, 1);
  printf("%d\n", ans);
}