#include <stdio.h>

int main(){
    int repeat;
    scanf("%d", &repeat);
    while (repeat--){
        int num;
        scanf("%d", &num);
        if (num < 0) num *= -1;
        int tmp = num, cnt = 0, ten = 1;
        do{
            tmp /= 10;
            cnt ++;
            ten *= 10;
        }while (tmp);
        ten /= 10;
        while (cnt--){
            if (cnt > 1) printf("%-2d", num / ten);
            else printf("%d\n", num / ten);
            num = num % ten;
            ten /= 10;
        }
    }
    return 0;
}