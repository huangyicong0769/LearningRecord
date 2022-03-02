#include <stdio.h>

int factorial(int);

int main(){
    int n;
    scanf("%d", &n);
    printf("%d\n", factorial(n));
    return 0;
}

int factorial(int n){
    int fact = 1;
    for (register int i = 1; i <=n; i++) fact*=i;
    return fact;
}