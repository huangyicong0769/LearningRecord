#include <stdio.h>
#include <string.h>
void fsort(char *color[ ], int n);

int main(void )
{
    int i;
    char *pcolor[ ] = {"red", "blue", "yellow", "green", "black"};
    void fsort(char *color[ ], int n);

    fsort(pcolor, 5);   /* 调用函数 */
    for(i = 0; i < 5; i++) 
        printf("%s ", pcolor[i]);
    printf("\n");
    return 0;
}    


/* 请在这里填写答案 */
void fsort(char *color[ ], int n){
    for (register int i = 0; i < n; i++)
        for (register int j = i + 1; j < n; j++)
            if (strcmp(color[i], color[j]) > 0){
                void *tmp = color[i];
                color[i] = color[j];
                color[j] = tmp;
            }
}
