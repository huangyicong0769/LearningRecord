#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

ll M[100010], A[100010];

ll exgcd(ll a, ll b, ll& x, ll& y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    ll d=exgcd(b, a%b, x, y),
       z=x;
    x=y; y=z-y*(a/b);
    return d;
}

int main(){
    freopen("input.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%lld%lld", &M[i], &A[i]);
    ll x=0, m=1;
    for (int i=0; i<N; i++){
        ll b=A[i]-x,
           a=m,
           xx, yy;
        if (b%exgcd(a, M[i], xx, yy)==0){
            xx=(xx%b+b)%b;
            printf("%lld %lld %lld %lld %lld\n", a, b, M[i], xx, x);
            x=x+xx*m;
        }else{
            printf("-1\n");
            break;
        }
        m*=M[i];
    }
    printf("%lld\n", x);
}