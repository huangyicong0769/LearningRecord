#include <stdio.h>

int main(){
  int n;
  scanf("%d", &n);
  double sum = 0, item = 1;
  for (register int i = 1; i <= n + 1; i++){
    sum += item;
    item /= i;
  }
  printf("%.8lf\n", sum);
}