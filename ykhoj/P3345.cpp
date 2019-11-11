#include <iostream>
#include <cstdio>
#include <cstring>
#define reg register
#define il inline
#define f1(a, b, c) for (reg int a=b; a<=c; a++)
#define f2(a, b, c) for (reg int a=b; a>=c; a--)
#define ll long long 
#define MAXN 200000
using namespace std;

ll a[MAXN+10], t[MAXN+10], r[MAXN+10], N;

il ll read();
il ll lowbit(const ll &);
il ll ask(ll);
il void add(ll, const ll &);

int main(){
    // freopen("input.txt", "r", stdin);
    N=read();
    f1(i, 1, N) a[i]=read();
    ll ans=0;
    f2(i, N, 1) r[i]+=ask(N)-ask(a[i]-1), add(a[i], 1);
    memset(t, 0, sizeof(t));
    f1(i, 1, N) ans+=(ask(N)-ask(a[i]-1))*r[i], add(a[i], 1);
    printf("%lld ", ans);
    ans=0;
    memset(r, 0, sizeof(r));
    memset(t, 0, sizeof(t));
    f2(i, N, 1) r[i]+=ask(a[i]-1), add(a[i], 1);
    memset(t, 0, sizeof(t));
    f1(i, 1, N) ans+=ask(a[i]-1)*r[i], add(a[i], 1);
    printf("%lld\n", ans);
}

il ll read(){
    ll x=0; char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar());
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x;
}

il ll lowbit(const ll & x){
    return x&(-x);
}

il ll ask(ll x){
    ll ans=0;
    for (; x; x-=lowbit(x)) ans+=t[x];
    return ans;
}

il void add(ll x, const ll & y){
    for (; x<=N; x+=lowbit(x)) t[x]+=y;
}