#include <stdio.h>

int main(){
  int a, sum = 0;
  scanf("%d", &a);
  while (a > 0) {
    if (a % 2) sum += a;
    scanf("%d", &a);
  }
  printf("sum=%d\n", sum);
}