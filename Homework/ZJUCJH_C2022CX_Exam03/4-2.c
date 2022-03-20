#include <stdio.h>

int main(){
  int N;
  scanf("%d", &N);
  double sum = 0;
  for (register int i = 1; i <= N; i++) sum += 1.0/(2*i - 1);
  printf("sum = %.6lf\n", sum);
  return 0;
}