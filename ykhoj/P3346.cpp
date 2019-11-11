#include <iostream>
#include <cstdio>
#define reg register
#define il inline
#define ll long long
#define f(a, b, c) for (reg int a=b; a<=c; a++)
#define lowbit(a) (a&(-a))
#define MAXN 100010
using namespace std;

ll s[MAXN], b[2][MAXN];
int N, Q;

il ll ask(const int &k, int x){
    ll ans=0;
    for (; x; x-=lowbit(x)) ans+=b[k][x];
    return ans;
}

il void add(const int &k, int x, const int y){
    for (; x<=N; x+=lowbit(x)) b[k][x]+=y;
}

il ll read(){
    reg ll x=0, f=1; reg char ch=getchar();
    for(; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for(; ch>='0' && ch<='9'; ch=getchar()) x=x*10+(ch-'0');
    return x*f;
}

int main(){
    scanf("%d%d", &N, &Q);
    f(i, 1, N) {
        int t; scanf("%d", &t);
        s[i]=s[i-1]+t;
    }
    for (; Q; Q--) {
        char ch[2]; int l, r, c;
        scanf("%s%d%d", ch, &l, &r);
        if (ch[0]=='C'){
            scanf("%d", &c);
            add(0, l, c);
            add(0, r+1, -c);
            add(1, l, l*c);
            add(1, r+1, -(r+1)*c);
        }
        if (ch[0]=='Q'){
            ll ans=s[r]+(r+1)*ask(0, r)-ask(1, r);
            ans-=s[l-1]+l*ask(0, l-1)-ask(1, l-1);
            printf("%lld\n", ans);
        }
    }
}
