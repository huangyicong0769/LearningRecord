#include <cstdio>
#define reg register
#define il inline

typedef long long ll;

il ll read() {
  reg ll x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar());
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il ll find(ll x) {
  reg ll ans = 0, l = 1, r = 5e7;
  while (l <= r) {
    reg ll mid = (l + r) >> 1;
    if (x >= 2LL * mid * (mid + 1)) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}

int main() {
  // f(i, 1, 10) printf("%lld ", f[i]); puts("");
  int T = read();
  while (T--) {
    reg ll m = read();
    if (m < 4) {
      puts("0");
      continue;
    }
    reg ll k = find(m);
    m -= 2LL * k * (k + 1);
    reg ll ans = k * k;
    if (m >= 2LL * k + 1) m -= 2LL * k + 1, ans += k;
    ans += (--m)/2;
    printf("%lld\n", ans);
  }
}