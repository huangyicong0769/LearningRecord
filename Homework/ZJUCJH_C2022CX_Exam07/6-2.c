#include <stdio.h>

int isNotPrime[1005];

int main(){
    int M, N;
    scanf("%d%d", &M, &N);
    isNotPrime[0] = 1;
    isNotPrime[1] = 1;
    for (register int i = 2; i <= N; i++)
        if (isNotPrime[i] == 0)
            for (register int j = i + i; j <=N; j += i)
                isNotPrime[j] = 1;
    int sum = 0, cnt = 0;
    for (register int i = M; i <= N; i++)
        if (isNotPrime[i] == 0){ 
            sum += i;
            cnt ++;
        }
    printf("%d %d\n", cnt, sum);
    return 0;
}