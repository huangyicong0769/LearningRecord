#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define SIZE 1006
#define il inline
#define reg register
#define f(i, s, t) for (reg int i = s; i != t; i++)
using namespace std;

const int MOD = 1000000007;
int T, M, N, a[SIZE], b[SIZE], c[SIZE], f[SIZE][SIZE];

il int ask(int x) {
  reg int ans = 0;
  for (; x; x -= x & -x) (ans += c[x]) %= MOD;
  return ans;
}

il void add(int x, int y) {
  for (; x <= N + 1; x += x & -x) (c[x] += y) %= MOD;
}

int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%d", &T);
  f(tt, 0, T) {
    memset(f, 0, sizeof(f));
    scanf("%d%d", &N, &M);
    f(i, 1, N + 1) scanf("%d", &a[i]);
    memcpy(b, a, sizeof(a));
    sort(b + 1, b + N + 1);
    f(i, 1, N + 1) a[i] = lower_bound(b + 1, b + 1 + N, a[i]) - b + 1;
    a[0] = f[0][0] = 1;
    f(i, 1, M + 1) {
      memset(c, 0, sizeof(c));
      add(1, f[i - 1][0]);
      f(j, 1, N + 1) {
        f[i][j] = ask(a[j] - 1);
        add(a[j], f[i - 1][j]);
      }
    }
    reg int ans = 0;
    f(i, 1, N + 1)(ans += f[M][i]) %= MOD;
    printf("Case #%d: %d\n", tt + 1, ans);
  }
}