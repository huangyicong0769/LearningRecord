#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll& x, ll& y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    ll d=exgcd(b, a%b, x, y),
       t=x;
    x=y, y=t-y*(a/b);
    return d;
}

int main(){
    //freopen("input.txt", "r", stdin);
    ll a, b, x, y;
    scanf("%lld%lld", &a, &b);
    exgcd(a, b, x, y);
    printf("%lld\n", (x%b+b)%b);
}