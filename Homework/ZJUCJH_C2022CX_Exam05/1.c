#include <stdio.h>

int main(){
  int num = 0, sum = 0;
  for (scanf("%d", &num); num > 0; scanf("%d", &num))
    sum += (num % 2) * num;
  printf("%d\n", sum);
}