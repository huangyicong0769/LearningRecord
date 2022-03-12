#include <stdio.h>
#include <math.h>

int main(){
  double x;
  printf("Enter x: ");
  scanf("%lf", &x);
  printf("f(%.2lf) = %.2lf\n", x, x >= 0 ? sqrt(x) : (x+1)*(x+1)+2*x+1.0/x);
}