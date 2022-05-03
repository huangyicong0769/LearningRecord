#include <stdio.h>

int a[1007];

int scanfArr(int *a){
    int n;
    scanf("%d", &n);
    for (register int i = 0; i < n; i++)
        scanf("%d", a + i);
    return n;
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

int main(){
    int n = scanfArr(a);
    sort(n, a);
    int cnt = 0, cur = 0, ans = 0, ansNum = 0;
    for (register int i = 0; i < n; i++) {
        if (cur != a[i]) {
            if (cnt > ans){
                ans = cnt;
                ansNum = cur;
            }
            cur = a[i];
            cnt = 0;
        }
        cnt++;
    }
    if (cnt > ans){
        ans = cnt;
        ansNum = cur;
    }
    printf("%d %d\n", ansNum, ans);
}