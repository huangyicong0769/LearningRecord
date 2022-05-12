#include <stdio.h>
#include <string.h>

int isUpCase(char ch){
    return (ch >= 'A' && ch <= 'Z');
}

int main(){
    char str[87];
    gets(str);
    const int N = strlen(str);
    for (register int i = 0; i < N; i++)
        if (isUpCase(str[i])) 
            str[i] = 'Z' + ('A' - str[i]);
    puts(str);
}