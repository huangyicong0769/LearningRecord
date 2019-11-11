#include <cstdio>
#include <cstring>
#define reg register
#define f(i, s, t) for (reg int i=s; i<=t; i++)
using namespace std;

long long f[31][16][11][8][7], n[6];

int main(){
  while (1){
    int K;
    scanf("%d", &K);
    if (K==0) break;
    memset(f, 0, sizeof(f));
    memset(n, 0, sizeof(n));
    f[0][0][0][0][0]=1;
    f(i, 1, K) scanf("%lld", &n[i]);
    f(a1, 0, n[1]) f(a2, 0, n[2]) f(a3, 0, n[3]) f(a4, 0, n[4]) f(a5, 0, n[5]){
      if (a1<n[1]) f[a1+1][a2][a3][a4][a5]+=f[a1][a2][a3][a4][a5];
      if (a2<n[2] && a1>a2) f[a1][a2+1][a3][a4][a5]+=f[a1][a2][a3][a4][a5];
      if (a3<n[3] && a2>a3) f[a1][a2][a3+1][a4][a5]+=f[a1][a2][a3][a4][a5];
      if (a4<n[4] && a3>a4) f[a1][a2][a3][a4+1][a5]+=f[a1][a2][a3][a4][a5];
      if (a5<n[5] && a4>a5) f[a1][a2][a3][a4][a5+1]+=f[a1][a2][a3][a4][a5];
    }
    printf("%lld\n", f[n[1]][n[2]][n[3]][n[4]][n[5]]);
  } 
}