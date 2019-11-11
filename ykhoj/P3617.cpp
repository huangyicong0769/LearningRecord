#include <iostream>
#include <cstdio>
#define INT_MAX ((1LL<<60)-1)
using namespace std;

typedef long long ll;

ll N, X[200100], Y[200100], S[200100];

bool check(ll);

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // 
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        ll s;
        scanf("%lld%lld%lld", &X[i], &Y[i], &s);
        S[i]=s*1000;
    }
    ll l=0, r=INT_MAX;
    while (l<r){
        ll mid=(l+r)/2;
        if (check(mid)) r=mid; else l=mid+1;
    }
    double b=r/1000.0;
    #ifdef DEBUG
    printf("%lld\n", r);
    #endif // 
    printf("%.2lf\n", b);
}

bool check(ll V){
    #ifdef DEBUG
    printf("%d====\n", V);
    #endif // 
    double ti=0;
    for (int i=0; i<N; i++){
        ti+=S[i]/(double)V;
        #ifdef DEBUG
        printf("%.2lf %d %lld %lld %lld\n", ti, i, X[i], Y[i], S[i]);
        #endif // 
        if (ti<X[i]) ti=X[i];
        if (ti>Y[i]) return 0;
    }
    #ifdef DEBUG
    printf("!\n");
    #endif // 
    return 1;
}