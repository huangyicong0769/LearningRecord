#include <stdio.h>

void printStar(int blank, int starNum){
    for (register int j =0; j < blank; j++)
        printf(" ");
    for (register int i = 0; i < starNum; i++)
        printf("* ");
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    for (register int i = 1; i <= n; i += 2)
        printStar(n - i, i);
    for (register int i = n - 2; i > 0; i -= 2)
        printStar(n - i, i);
    return 0;
}