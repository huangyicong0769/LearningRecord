#include <stdio.h>

int isInArr(char x, int n, char *a){
    for (register int i = 0; i < n; i++)
        if (a[i] == x) return 1;
    return 0;
}

int main(){
    printf("Enter a string:");
    char ans[87];
    ans[0] = 0;
    for (register char ch = getchar(); ch != '\n'; ch = getchar())
        if (ch >= 'A' && ch <= 'Z' && !isInArr(ch, ans[0], ans + 1))
            ans[++ans[0]] = ch;
    ans[++ans[0]] = '\0';
    if (ans[0] == 1) 
        puts("Not Found");
    else printf("%s\n", ans + 1);
}