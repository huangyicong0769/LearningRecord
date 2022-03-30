#include <stdio.h>

int main(){
  int N;
  scanf("%d", &N);
  double sum = 0;
  for (register int i = 0; i < N; i++){
    double  fact = 1;
    for (register int j = 1; j <= i; j++) fact *= j;
    sum += 1.0 / fact;
  }
  printf("%.4lf\n", sum);
}