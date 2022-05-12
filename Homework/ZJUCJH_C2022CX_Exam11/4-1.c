#include <stdio.h>
#include <string.h>

int main(){
    char toFind, str[87];
    scanf("%c\n", &toFind);
    gets(str);
    const int N = strlen(str);
    for (register int i = N - 1; i >= 0; i--)
        if (toFind == str[i]) {
            printf("index = %d\n", i);
            goto FOUND;
        }
    printf("Not Found\n");
FOUND:
;
}