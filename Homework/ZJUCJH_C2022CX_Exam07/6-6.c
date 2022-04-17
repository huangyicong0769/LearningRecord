#include <stdio.h>
#include <math.h>

int isPrime(int n){
    for (register int i = 2; i <= sqrt(n); i++)
        if (n%i == 0) return 0;
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    int haveMN = 0;
    for (register int i = 2; i <= n; i++){
        int tmp = pow(2, i) - 1;
        if (isPrime(tmp)){
            haveMN = 1;
            printf("%d\n", tmp);
        }
    }
    if (haveMN == 0) printf("None\n");
}