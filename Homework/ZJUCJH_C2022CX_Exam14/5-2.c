#include <stdio.h>
char *match(char *s, char ch);      /* 函数声明 */
int main(void )
{
    char ch, str[80], *p = NULL;

    scanf("%s", str);
    getchar(); 
    ch = getchar();  
    if((p = match(str, ch)) != NULL)  
        printf("%s\n", p);
    else 
        printf("Not Found\n");
    return 0;
}


/* 请在这里填写答案 */
char *match(char *s, char ch){
    for (register int i = 0; s[i] != '\0'; i++)
        if (s[i] == ch) return s + i;
    return NULL;
}