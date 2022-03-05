#include <stdio.h>

int main(){
  double x;
  scanf("%lf", &x);
  printf("f(%.1lf) = %.1lf\n", x, x == 0 ? 0 : 1.0/x);
}