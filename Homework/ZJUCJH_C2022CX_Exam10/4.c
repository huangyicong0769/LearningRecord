#include <stdio.h>

int a[1007], b[5007], c[11];

int scanfArr(int *a){
    int n;
    scanf("%d", &n);
    for (register int i = 0; i < n; i++)
        scanf("%d", a + i);
    return n;
}

void printArr(int n, int *a){
    for (register int i = 0; i < n; i++)
        printf(" %d", a[i]);
    printf("\n");
}

void countDigital(int a, int *cnt){
    do{
        cnt[a%10]++;
        a /= 10;
    }while (a != 0);
}

int main(){
    int n = scanfArr(a);
    int totCnt[11] = {0};
    for (register int i = 0; i < n; i++)
        countDigital(a[i], totCnt);
    int maxCnt = 0;
    for (register int i = 0; i < 10; i++){
        if (totCnt[i] > maxCnt) {
            maxCnt = totCnt[i];
            c[0] = 0;
        }
        if (totCnt[i] == maxCnt) c[++c[0]] = i;
    }
    printf("%d:", maxCnt);
    printArr(c[0], c + 1);
}