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
        if ((i + 1) % 3 == 0 || i == n - 1) printf("%d\n", a[i]);
        else printf("%d ", a[i]);
}

int main(){
    int n = scanfArr(a);
    for (register int i = 1; i < n; i++)
        b[i] = a[i] - a[i - 1];
    printArr(n - 1, b + 1);
}