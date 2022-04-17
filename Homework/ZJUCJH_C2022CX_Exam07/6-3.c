#include <stdio.h>

int makeNum(int d, int n){
    int ret = 0;
    for (register int i = 0; i < n; i++){
        ret *= 10;
        ret += d;
    }
    // printf("%d\n", ret);
    return ret;
}

int main(){
    int a, n;
    scanf("%d%d", &a, &n);
    int sum = 0;
    for (register int i = 1; i <= n; i++)
        sum += makeNum(a, i);
    printf("s = %d\n", sum);
}