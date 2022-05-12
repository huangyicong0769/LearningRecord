#include <stdio.h>
#include <string.h>

int tf[128];
long long pow16[11];

int isLegal(char ch){
    return (ch >= 'A' && ch <= 'F' || ch >= '0' && ch <= '9');
}

void upCase(char *str){
    const int N = strlen(str);
    for (register int i = 0; i < N; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 'a' + 'A';
}

void clearStr(char *str){
    const int N = strlen(str);
    char ret[N];
    int isMinus = 0, haveLegal = 0, n = 0;
    for (register int i = 0; i < N; i++)
        if (str[i] == '-' && !haveLegal && !isMinus){
            isMinus = 1;
            ret[n++] = '-';
        }else if (isLegal(str[i])){
            haveLegal = 1;
            ret[n++] = str[i];
        }
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
        ret += tf[str[N - 1 -i]] * pow16[i];
    return ret * k;
}

int main(){
    for (register int i = 0; i < 10; i++)
        tf[i + '0'] = i;
    for (register int i = 'A'; i <= 'F'; i++)
        tf[i] = i - 'A' + 10;
    pow16[0] = 1;
    for (register int i = 1; i < 11; i++) pow16[i] = pow16[i - 1] * 16;
    char str[1005], ch;
    int n = 0;
    while ((ch = getchar()) != '#')
        str[n++] = ch;
    str[n++] = '\0';
    upCase(str);
    clearStr(str);
    printf("%s\n", str);
    printf("%d\n", transfrom(str));
}