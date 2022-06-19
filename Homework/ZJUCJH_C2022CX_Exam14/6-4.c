#include <stdio.h>

int notPrime[505];

int main(){
    notPrime[0] = notPrime[1] = 1;
    for (register int i = 2; i < 501; i++) 
        if (!notPrime[i]){
            for (register int j = 2*i; j < 501; j+=i) notPrime[j] = 1;
        }
    int m, n;
    scanf("%d%d", &m, &n);
    int cnt = 0, sum = 0;
    for (register int i = m; i <= n; i++){
        cnt += notPrime[i]^1;
        sum += (notPrime[i]^1) *i;
    }
    printf("%d %d\n", cnt, sum);
}