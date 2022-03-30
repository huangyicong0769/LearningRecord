#include <stdio.h>

int main(){
  int N, sum = 0, cnt = 0;
  scanf("%d", &N);
  do {
    cnt++;
    sum += N%10;
    N /= 10;
  }while (N);
  printf("%d %d\n", cnt, sum);
  return 0;
}