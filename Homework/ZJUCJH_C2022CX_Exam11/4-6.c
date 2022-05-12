#include <stdio.h>
#include <string.h>

int tf[128];
long long pow10[11];

int isLegal(char ch){
    return (ch >= '0' && ch <= '9');
}

void clearStr(char *str){
    const int N = strlen(str);
    char ret[N];
    int n = 0;
    for (register int i = 0; i < N; i++)
        if (isLegal(str[i]))
            ret[n++] = str[i];
    ret[n++] = '\0';
    for (register int i = 0; i < n; i++) 
        str[i] = ret[i];
}

int transfrom(char *str){
    int k = 1, ret = 0;
    if (str[0] == '-') {
        k = -1;
        str++;
    }
    const int N = strlen(str);
    for (register int i = 0; i < N; i++)
        ret += tf[str[N - 1 -i]] * pow10[i];
    return ret * k;
}

int main(){
    for (register int i = 0; i < 10; i++)
        tf[i + '0'] = i;
    pow10[0] = 1;
    for (register int i = 1; i < 11; i++) pow10[i] = pow10[i - 1] * 10;
    char str[1005], ch;
    int n = 0;
    while ((ch = getchar()) != '\n')
        str[n++] = ch;
    str[n++] = '\0';
    clearStr(str);
    printf("%d\n", transfrom(str));
}