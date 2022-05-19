#include <iostream>
#include <cstdio>

int max(const int &a, const int &b){
    return (a > b ? a : b);
}

int main(){
    int n;
    scanf("%d", &n);
    int a[n+7];
    for (register int i = 1; i <= n; i++) scanf("%d", a+i);
    int ans = 0;
    for (register int i = 1; i <= n; i++, ans++)
        for (register int maxNum = a[i]; i < (maxNum = max(maxNum, a[i])); i++);
    printf("%d\n", ans); 
}