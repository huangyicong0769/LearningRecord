#include <stdio.h>

int main(){
  double s = 0, exp;
  scanf("%lf", &exp);
  register int i;
  for (i = 1; 1.0/i > exp; i += 3)
    s += (i % 2 ? 1.0 : -1.0) / i;
  s += (i % 2 ? 1.0 : -1.0) / i;
  printf("sum = %.6lf\n", s);
  return 0;
}