#include <cstdio>
#include <cstring>
#include <iostream>
#define reg register
#define f(i, s, t) for (reg int i = s; i != t; i++)
using namespace std;

int m[106], cnt[80], s[80], f[2][80][80], N, M, tot;

inline int count1(int x) {
  reg int ans = 0;
  for (; x; x >>= 1)
    if (x & 1) ans++;
  return ans;
}

int main() {
  cin >> N >> M;
	f(i, 1, N+1) f(j, 0, M) {
		char tmp; cin >> tmp;
		if(tmp == 'H') m[i] |= (1 << (M-1-j));
	}
  tot = 0;
  f(i, 0, 1 << M) {
    // cout << i << endl;
    if (i & (i << 1)) continue;
    if (i & (i << 2)) continue;
    s[tot] = i;
    cnt[tot++] = count1(i);
  }
  int ans = 0;
  memset(f, -1, sizeof(f));
  f[0][0][0] = 0;
  f(i, 0, tot) {
    // cout << i << endl;
    if (m[1] & s[i]) continue;
    f[1][i][0] = cnt[i];
    ans = max(ans, cnt[i]);
  }
  f(i, 2, N + 1) f(j, 0, tot) {
    // cout << i << ' ' << j << endl;
    if (m[i] & s[j]) continue;
    f(k, 0, tot) {
      if (m[i - 1] & s[k]) continue;
      if (s[j] & s[k]) continue;
      reg int t = 0;
      f(l, 0, tot) {
        if (f[(i-1) % 2][k][l] == -1) continue;
        if (m[i - 2] & s[l]) continue;
        if (s[j] & s[l] || s[l] & s[k]) continue;
        t = max(t, f[(i-1) % 2][k][l]);
      }
      f[i % 2][j][k] = max(t + cnt[j], f[i % 2][j][k]);
      if (i == N) ans = max(ans, f[i % 2][j][k]);
    }
  }
  printf("%d\n", ans);
}
