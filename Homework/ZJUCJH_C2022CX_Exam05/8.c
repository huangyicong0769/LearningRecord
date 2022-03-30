#include <stdio.h>

int main(){
  double sum = 1, x, exp = 0.00001, tmp = 1, fact = 1, i = 0;
  scanf("%lf", &x);
  do{
    tmp *= x;
    fact *= ++i;
    sum += tmp / fact;
  }while (tmp / fact >= exp);
  printf("%.4lf\n", sum);
  return 0;
}