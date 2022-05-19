#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int n;
    scanf("%d", &n);
    int a[n + 1], b[n + 1], p[n+1], cnt[n + 1] = {0};
    for (register int i = 0, a; i < n; i++) {
        scanf("%d", &a);
        cnt[a] = i + 1;
    }
    for (register int i = 0, b; i < n; i++){
        scanf("%d", &b);
        p[i] = cnt[b];
    }
    for (register int i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\n");
}