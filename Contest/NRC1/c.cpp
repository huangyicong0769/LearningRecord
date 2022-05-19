#include <iostream>
#include <cstdio>

int c[4], b[4];

int main(){
    for (register int i = 0; i < 4; i++)
        scanf("%d", c + i);
    for (register int i = 0; i < 4; i++)
        for (register int j = 0; j < 4; j++){
            int a;
            scanf("%d", &a);
            b[j] += a;
        }
    for (register int i = 0; i < 4; i++)
        if (b[i] < c[i]){
            puts("NO");
            return 0;
        }
    puts("YES");
    return 0;
}