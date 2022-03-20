#include <stdio.h>
#include <math.h>

int main(){
  int n;
  scanf("%d", &n);
  double ans = 0;
  for (register int i = 1; i <= n; i++) ans += sqrt(i);
  printf("%.2lf\n", ans);
}