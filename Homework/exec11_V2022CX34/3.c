#include <stdio.h>
#include <string.h>

void input(const char *oStr, char * str){
    printf("%s", oStr);
    gets(str);
}

int isPalindromic(const char *str){
    const int N = strlen(str);
    for (register int i = 0; i < N; i++)
        if (str[i] != str[N - 1 -i]) return 0;
    return 1;
}

int main(){
    char str[101];
    input("Enter a string :", str);
    if (isPalindromic(str)) puts("YES");
    else puts("NO");
}