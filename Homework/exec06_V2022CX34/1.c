#include <stdio.h>

int countDigit( int number, int digit ){
  int cnt = 0;
  if (number < 0) number *= -1;
  do{
    if (number % 10 == digit) cnt++;
    number /= 10; 
  }while (number);
  return cnt;
}

int main(){
  int number, digit;
  printf("Enter number: "); scanf("%d", &number);
  printf("Enter digit: "); scanf("%d", &digit);
  printf("Number of digit %d in %d: %d\n", digit, number, countDigit(number, digit));
  return 0;
}
