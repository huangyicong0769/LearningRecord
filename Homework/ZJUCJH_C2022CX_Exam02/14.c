#include <stdio.h>

int main(){
  double x;
  scanf("%lf", &x);
  if (x < 0) printf("Invalid Value!\n");
  else printf("cost = %.2lf\n", x <= 50 ? 0.53*x : 0.53*50 + 0.58*(x-50));
  return 0;
}