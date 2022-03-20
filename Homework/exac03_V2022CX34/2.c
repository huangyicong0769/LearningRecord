#include <stdio.h>

int main(){
  int m, n;
  printf("Enter m:"); scanf("%d", &m);
  printf("Enter n:"); scanf("%d", &n);
  double ans = 0;
  for(register int i = m; i <= n; i++) ans += i*i + 1.0/i;
  printf("sum = %.6lf\n", ans);
  return 0;
}