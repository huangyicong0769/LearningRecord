#include <cstdio>
#include <iostream>

const int MOD = 1000000000+7;

int f[100005];

int max(const int &a, const int &b){
    return (a > b ? a : b);
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    f[0] = 1;
    f[1] = 1;
    for (register int i = 2; i <= max(n, m); i++)
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    printf("%d\n", (f[n] + f[m] - 1)%MOD * 2 %MOD);
}