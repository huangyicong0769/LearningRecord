#include <stdio.h>
#include <math.h>

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    long long v=0, k;
    while(1){
        char c;
        if (scanf("%c", &c)==EOF) break;
        if (c>='0' && c<='9') v+=c-'0';
    }
    k=v;
    for (long long i=2; i<=sqrt(v); i++)
        if (v%i==0){
            k=i;
            break;
        }
    printf("%lld\n", k);
}