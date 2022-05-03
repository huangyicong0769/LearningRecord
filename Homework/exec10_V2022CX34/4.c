#include <stdio.h>
#include <string.h>

void intputStr(const char* s, char* str){
    printf("%s", s);
    scanf("%s", str);
}

void sort(int n, char* a){
    for (register int i = 0; i < n; i++)
        for (register int j = i + 1; j < n; j++)
            if (a[i] > a[j]){
                char t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

int main(){
    char str[87];
    intputStr("Enter a string:", str);
    sort(strlen(str), str);
    for (register int i = 0; str[i] != '\0'; i++){
        if (i && str[i] == str[i - 1]) continue;
        putchar(str[i]);
    }
    printf("\n");
}