#include <stdio.h>

int main(){
  int sum = 0;
  for (register int i = 0; i < 4; i++){
    int a;
    scanf("%d", &a);
    sum += a;
  }
  printf("Sum = %d; Average = %.1lf\n", sum, sum/4.0);
  return 0;
}