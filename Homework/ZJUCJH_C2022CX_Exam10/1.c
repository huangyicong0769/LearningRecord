#include <stdio.h>

int a[13];

void sort(int, int*);
void printArr(int, int *);

int main(){
    int n;
    scanf("%d", &n);
    for (register int i = 0; i < n; i++) 
        scanf("%d", a + i);
    sort(n, a);
    printArr(n, a);
}


void sort(int n, int* a){
    for (register int i = 0; i < n; i++)
        for (register int j = i + 1; j < n; j++)
            if (a[i] < a[j]){
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

void printArr(int n, int *a){
    for (register int i = 0; i < n - 1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n - 1]);
}