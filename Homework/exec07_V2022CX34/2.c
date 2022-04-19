#include <stdio.h>

int countDigit(int number, const int digit){
    if (number < 0) number *= -1;
    int cnt = 0;
    do{
        if (number%10 == digit) cnt++;
        number /= 10;
    }while (number != 0);
    return cnt;
}

int main(){
    int number, digit;
    printf("Enter number:"); scanf("%d", &number);
    printf("Enter digit:"); scanf("%d", &digit);
    printf("Number of digit %d in %d: %d\n", digit, number, countDigit(number, digit));
    return 0;
}