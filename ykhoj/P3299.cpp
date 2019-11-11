#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define il inline
#define reg register
#define ll long long
using namespace std;

int N, M, T, ACT;
ll act[9][9], A[60][65][65], AQ[65][65], f[65];

string s[10];

il void _debug(const ll a[65][65]){
    for (reg int i=0; i<=M*N; printf("\n"), i++) for (reg int j=0; j<=M*N; j++) printf("%lld ", a[i][j]);
    printf("\n");
}
il void _debug(const ll a[65]){
    for (reg int i=0; i<=M*N; i++) printf("%lld ", a[i]);
    printf("\n\n");
}
il int num(const ll &, const ll &);
il void init();
il void mul(ll[65], ll[65][65]);
il void mul(ll[65][65], ll[65][65]);

int main(){
    // freopen("output.txt", "w", stdout);
    scanf("%d%d%d%d", &N, &M, &T, &ACT);
    for (reg int i=1; i<=N; i++) for (reg int j=1; j<=M; j++) {
        reg char ch=getchar();
        for (; ch<'0' || ch>'9'; ch=getchar());
        act[i][j]=ch-'0'; 
    }
    for (reg int i=0; i<ACT; i++) cin>>s[i];
    init();
    // for (reg int i=0; i<T%60; i++) _debug(A[i]);
    for (reg int Q=T/60; Q; Q>>=1){
        // _debug(AQ);
        if (Q&1) mul(f, AQ);
        mul(AQ, AQ);
    }
    for (reg int i=0; i<T%60; i++) mul(f, A[i]);
    ll ans=-1;
    for (reg int i=1; i<=N*M; i++) ans=max(ans, f[i]);
    printf("%lld\n", ans);
}

il int num(const ll & x, const ll & y) {return (x-1)*M+y;}

il void init(){
    for (reg int i=0; i<60; i++){
        // printf("!%d\n", i);
        A[i][0][0]=1;
        for (reg int x=1; x<=N; x++) for (reg int y=1; y<=M; y++) {
            reg char ch=s[act[x][y]][i%s[act[x][y]].size()];
            // printf("  %d %d %c\n", x, y, ch);
            if (ch=='N' && x>1) A[i][num(x, y)][num(x-1, y)]=1;
            if (ch=='W' && y>1) A[i][num(x, y)][num(x, y-1)]=1;
            if (ch=='S' && x<N) A[i][num(x, y)][num(x+1, y)]=1;
            if (ch=='E' && y<M) A[i][num(x, y)][num(x, y+1)]=1;
            if (ch>='0' && ch<='9') A[i][0][num(x, y)]=ch-'0', A[i][num(x, y)][num(x, y)]=1;
        }
        // _debug(A[i]);
    }
    memcpy(AQ, A[0], sizeof(A[0]));
    for (reg int i=1; i<60; i++) mul(AQ, A[i]);
    // _debug(AQ);
    f[0]=1;
}

il void mul(ll f[65], ll a[65][65]){
    ll c[65]={0};
    // c[0]=1;
    for (reg int j=0; j<=M*N; j++) for (reg int k=0; k<=M*N; k++) c[j]+=f[k]*a[k][j];
    // printf("?%d\n", c[6]);
    memcpy(f, c, sizeof(c));
    // printf("??%d\n", f[6]);
    // f[0]=1;
}

il void mul(ll a[65][65], ll b[65][65]){
    ll c[65][65]={0};
    // c[0][0]=1;
    for (reg int i=0; i<=M*N; i++) for (reg int k=0; k<=M*N; k++) if (a[i][k]) for (reg int j=0; j<=M*N; j++)  c[i][j]+=a[i][k]*b[k][j];
    memcpy(a, c, sizeof(c));
    // a[0][0]=1;
}