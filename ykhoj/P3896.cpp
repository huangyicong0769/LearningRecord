#include <iostream>
#include <cstdio>
using namespace std;

long long M, N;

long long superPower(long long n, long long q, long long p){
    if (q==0) return 1;
    if (q==1) return n;
    long long t=superPower(n, q/2, p);
    if (q%2)
        return t*t%p*n%p;
    else
        return t*t%p;
}

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%lld%lld", &M, &N);
    long long t1=superPower(M, N, 100003),
        t2=M*superPower(M-1, N-1, 100003)%100003,
        ans=(t1-t2);
    while (ans<0) ans+=100003;
    printf("%lld\n", ans);
}