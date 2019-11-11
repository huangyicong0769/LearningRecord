#include <iostream>
#include <cstdio>
using namespace std;

int N, M, K, X;

int superPower(int n, int q, int p){
    int ans=1;
    while (q){
        if (q & 1) ans=(long long) ans*n%p;
        n=n*n%p;
        q>>=1;
    }
    return ans;
}

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d%d%d%d", &N, &M, &K, &X);
    int nk=superPower(10, K, N),
        ans=X;
    for (int i=0; i<nk; i++)
        ans=(ans+M)%N;
    printf("%d\n", ans);
    return 0;
}