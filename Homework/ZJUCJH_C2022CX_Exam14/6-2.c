#include <stdio.h>
#include <string.h>

const char* color[] = {"red", "blue", "yellow", "green", "black"};

int main(){
    char str[10];
    scanf("%s", str);
    for (register int i = 0; i < 5; i++)
        if (strcmp(str, color[i]) == 0){
            printf("%d\n", i+1);
            goto Founded;
        }
    printf("Not Found\n");
    return 0;
Founded:
    return 0;
}