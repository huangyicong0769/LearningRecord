#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    if (N < 2) printf("1\n");
    else {
        int pre = 1, now = 1, cnt = 2;
        do{
            int tmp = now;
            now = pre + now;
            pre = tmp;
            cnt ++;
        }while(now < N);
        printf("%d\n", cnt);
    }
    return 0;
}