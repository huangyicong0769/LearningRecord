#include <iostream>
#include <cstdio>
#include <cstring>
#define reg register
#define f(a, b, c) for (reg int a=b; a<=c; a++) 
#define ll long long 
using namespace std;

ll a[31];

inline ll read();

int main(){
    for (reg int K=read(); K; K--){
        memset(a, 0, sizeof(a));
        const int N=read();
        f(i, 1, N) a[i]=read();
        f(i, 1, N) a[i]^=read(), a[i]|=1<<i;
        for (reg int i=read(), j=read(); i && j; i=read(), j=read()) 
            a[j]|=1<<i;
        ll ans=1;
        f(i, 1, N){
            f(j, i+1, N) if (a[j]>a[i]) swap(a[j], a[i]);
            if (a[i]==0) {
                ans=1<<(N-i+1);
                break;
            }
            if (a[i]==1) {
                ans=0;
                break;
            }
            for (reg int k=N; k; k--)
                if (a[i]>>k&1){
                    f(j, 1, N) if (i!=j && a[j]>>k&1) a[j]^=a[i];
                    break;
                }
        }
        if (ans) printf("%lld\n", ans);
        else puts("-1");
    }
}

inline ll read(){
    reg ll x=0; reg char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch==EOF) return EOF;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x;
}