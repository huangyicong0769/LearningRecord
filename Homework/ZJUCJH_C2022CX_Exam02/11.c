#include <stdio.h>
#include <math.h>

int main(){
  double m, y, r;
  scanf("%lf%lf%lf", &m, &y, &r);
  printf("interest = %.2lf\n", m*pow(1+r, y) - m);
}