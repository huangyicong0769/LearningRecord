#include <stdio.h>

int a[23], b[23], c[47];

int scanfArr(int *a){
    int n;
    scanf("%d", &n);
    for (register int i = 0; i < n; i++)
        scanf("%d", a + i);
    return n;
}

int isInArr(int x, int n, int *a){
    for (register int i = 0; i < n; i++)
        if (a[i] == x) return 1;
    return 0;
}

void printArr(int n, int *a){
    for (register int i = 0; i < n - 1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n - 1]);
}

int main(){
    int n1 = scanfArr(a),
        n2 = scanfArr(b);
    for (register int i = 0; i < n1; i++)
        if (!isInArr(a[i], n2, b) && !isInArr(a[i], c[0], c + 1))
            c[++c[0]] = a[i];
    for (register int i = 0; i < n2; i++)
        if (!isInArr(b[i], n1, a) && !isInArr(b[i], c[0], c + 1))
            c[++c[0]] = b[i];
    printArr(c[0], c + 1);
}