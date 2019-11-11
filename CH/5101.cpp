#include <cstdio>
#include <iostream>
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
using namespace std;

int f[3005][3005], a[3005], b[3005];

int main() {
  int N;
  scanf("%d", &N);
  f(i, 1, N) scanf("%d", &a[i]);
  f(i, 1, N) scanf("%d", &b[i]);
  f[0][0]=1;
  f(i, 1, N){
    reg int val=0;
    f (j, 1, N){
      if (a[i]==b[j]) f[i][j]=val+1;
      else f[i][j]=f[i-1][j];
      if (b[j]<a[i]) val=max(val, f[i-1][j]);
    }
  }
  reg int ans=0;
  f(i, 1, N) ans=max(ans, f[N][i]);
  printf("%d\n", ans);
}