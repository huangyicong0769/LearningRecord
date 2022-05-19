#include <iostream>
#include <cstdio>

int main(){
    int a, b, ans = 0;
    for (scanf("%d%d", &a, &b); a <= b; a*=3, b*=2) ans++;
    printf("%d\n", ans);
}