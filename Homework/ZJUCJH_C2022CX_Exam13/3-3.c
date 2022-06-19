#include <stdio.h>

void hollowPyramid ( int n );

int main()
{    
    int n;

    scanf("%d", &n);
    hollowPyramid ( n );

    return 0;
}

/* 你的代码将被嵌在这里 */
void hollowPyramid(int n){
    for (register int i = 1; i < n; i++){
        for (register int j = 0; j < n - i; j++) putchar(' ');
        printf("%d", i);
        if (i == 1){
            printf("\n");
            continue;
        }
        for (register int j = 0; j < 2*i - 3; j++) putchar(' ');
        printf("%d\n", i);
    }
    for (register int i = 0; i < 2*n - 1; i++) printf("%d", n);
    printf("\n");
}