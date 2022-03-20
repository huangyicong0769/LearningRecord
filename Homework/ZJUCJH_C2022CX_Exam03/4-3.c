#include <stdio.h>

int main(){
  int n;
  scanf("%d", &n);
  double sum = 0;
  for (register int i = 1; i <= n; i++) sum += (i%2 ? 1.0 : -1.0)/(3*i - 2);
  printf("sum = %.3lf\n", sum);
}