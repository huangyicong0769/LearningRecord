#include <stdio.h>

void dectobin( int n );

int main()
{
    int n;
    
    scanf("%d", &n);
    dectobin(n);
    
    return 0;
}

/* 你的代码将被嵌在这里 */

void solve(int n){
    if (n == 0) return;
    solve(n/2);
    printf("%d", n%2);
}

void dectobin(int n){
    if (n == 0) printf("0");
    else solve(n);
}