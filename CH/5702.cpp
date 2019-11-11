#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#define reg register
#define ll long long
#define f(i, s, t) for (reg int i = s; i != t; i++)
using namespace std;

string s1, s2;
int n1, n2;
ll ans, f[106][32];

int main() {
  while (cin >> s2 >> n2 >> s1 >> n1) {
    memset(f, 0, sizeof(f));
    f(i, 0, s1.size()) {
      f[i][0] = 0;
      reg int pos = i;
      f(j, 0, s2.size()) {
        reg int cnt = 0;
        while (s1[pos] != s2[j]) {
          (++pos) %= s1.size();
          if (++cnt >= s1.size()) {
            cout << 0 << endl;
            goto part;
          }
        }
        (++pos) %= s1.size();
        f[i][0] += cnt + 1;
      }
    }
    f(j, 1, 31) f(i, 0, s1.size()) f[i][j] =
        f[i][j - 1] + f[(i + f[i][j - 1]) % s1.size()][j - 1];
    ans = 0;
    f(i, 0, s1.size()) {
      reg ll x = i, cnt = 0;
      for (reg int j = 30; j >= 0; j--)
        if (x + f[x % s1.size()][j] <= s1.size() * n1)
          x += f[x % s1.size()][j], cnt += 1 << j;
      ans = max(ans, cnt);
    }
    printf("%lld\n", ans / n2);
  part:;
  }
}