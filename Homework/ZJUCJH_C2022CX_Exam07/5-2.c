#include <stdio.h>

int reverse( int number );
    
int main()
{
    int n;

    scanf("%d", &n);
    printf("%d\n", reverse(n));

    return 0;
}

/* 你的代码将被嵌在这里 */
int reverse(int number){
    int ret = 0, sign = 1;
    if (number < 0){
        sign = -1;
        number *= -1;
    }
    do{
        ret *= 10;
        ret += number % 10;
        number /= 10;
    }while (number != 0);
    return ret * sign;
}