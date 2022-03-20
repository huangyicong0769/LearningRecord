#include <stdio.h>

int main(){
  int N;
  scanf("%d", &N);
  double sum = 0;
  for (register int i = 1; i <= N; i++) 
    sum += (i%2 ? 1.0 : -1.0)*i/(2*i - 1);
  printf("%.3lf\n", sum);
  return 0;
}