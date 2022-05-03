#include <stdio.h>

int a[13];
void printArr(int, int *);

int main(){
    int n;
    scanf("%d", &n);
    for (register int i = 0; i < n; i++) 
        scanf("%d", a + i);
    int index = 0;
    for (register int i = 0; i < n; i++)
        if (a[index] > a[i]) index = i;
    int temp = a[index];
    a[index] = a[0];
    a[0] = temp;
    for (register int i = 0; i < n; i++)
        if (a[index] < a[i]) index = i;
    temp = a[index];
    a[index] = a[n - 1];
    a[n - 1] = temp;
    printArr(n, a);
}

void printArr(int n, int *a){
    for (register int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}