#include <stdio.h>

int a[13], b[13];

int scanfArr(int *a){
    int n;
    scanf("%d", &n);
    for (register int i = 0; i < n; i++)
        scanf("%d", a + i);
    return n;
}

void printArr(int n, int *a){
    for (register int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(){
    int n = scanfArr(a), x;
    scanf("%d", &x);
    a[n] = x + 1;
    for (register int i = 0, j = 0; j <= n; j++)
        if (x < a[i]) b[j] = x, x = a[n - 1] + 1;
        else b[j] = a[i++];
    printArr(n + 1, b);
}