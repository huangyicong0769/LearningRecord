#include <iostream>
#include <cstdio>
using namespace std;
#define reg register int  
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline
#define int __int128

const int SN = 101;
int a[SN], f[SN][SN], p[SN], N, M; 

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar());
  for (; ch >='0' && ch <='9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il int print(int a){
  if (!a) return 0;
  print(a/10);
  putchar(a%10 + '0');
}

il int dp(int x) {
  f(i, 1, M) f[i][i] = a[i] * p[M];
  f(d, 1, M - 1) f(l, 1, M - d) {
    reg r = l + d;
    f[l][r] = max(f[l + 1][r] + a[l] * p[M - d], f[l][r - 1] + a[r] * p[M - d]);
  }
  return f[1][M];
}

signed main(){
  p[0] = 1;
  f(i, 1, 100) p[i] = p[i - 1] * 2;
  // print(p[1]);
  N = read(), M = read();
  reg ans = 0;
  f(i, 1, N) {
    f(j, 1, M) a[j] = read();
    ans += dp(i);
  }
  ans == 0 ? puts("0") : print(ans);
}