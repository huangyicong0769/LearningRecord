#include <stdio.h>
#include <string.h>

int tf[128];
const char *NAME[] = {"uppercase", "lowercase", "blank", "digit", "others"};

void init(){
    for (register int i = 0; i < 128; i++) tf[i] = 4; 
    for (register int i = 0; i < 26; i++){
        tf[i + 'A'] = 0;
        tf[i + 'a'] = 1;
    }
    tf[' '] = 2;
    for (register int i = 0; i < 10; i++)
        tf[i + '0'] = 3;
}

int main(){
    init();
    printf("Enter a string:");
    int cnt[4] = {0};
    for (register char ch = getchar(); ch != '\n'; ch = getchar())
        cnt[tf[ch]]++;
    for (register int i = 0; i < 5; i++)
        printf("%s: %d\n", NAME[i], cnt[i]);
}