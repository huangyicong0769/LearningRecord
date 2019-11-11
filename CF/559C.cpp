#include <algorithm>
#include <cstdio>
#include <iostream>
#define il inline
#define reg register
#define f(i, s, t) for (reg int i = s; i != t; i++)
using namespace std;
typedef long long ll;

const int SIZE = 2006, P = 1000000007;
int H, W, N, f[SIZE];
ll ft[200006], ftInv[200006];
pair<int, int> a[SIZE];

il ll pow(ll a, int n) {
  reg ll ans = 1;
  for (; n; n >>= 1, a = a * a % P)
    if (n & 1) ans = ans * a % P;
  return ans;
}
il int C(int n, int m) { return ft[n] * ftInv[m] % P * ftInv[n - m] % P; }

int main() {
  ft[0] = 1, ftInv[0] = 1;
  f(i, 1, 200001) {
    ft[i] = ft[i - 1] * i % P;
    ftInv[i] = pow(ft[i], P - 2);
  }
  scanf("%d%d%d", &H, &W, &N);
  f(i, 1, N + 1) scanf("%d%d", &a[i].first, &a[i].second);
  sort(a + 1, a + 1 + N);
  a[N + 1].first = H, a[N + 1].second = W;
  f(i, 1, N + 2) {
    f[i] = C(a[i].first + a[i].second - 2, a[i].first - 1);
    f(j, 1, i) {
      if (a[j].first > a[i].first || a[j].second > a[i].second) continue;
      f[i] = (f[i] - (ll)f[j] *
                         C(a[i].first - a[j].first + a[i].second - a[j].second,
                           a[i].first - a[j].first) %
                         P) %
             P;
    }
  }
  printf("%d\n", (f[N + 1] + P) % P);
}