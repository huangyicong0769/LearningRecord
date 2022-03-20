#include <stdio.h>

int main(){
  int n;
  scanf("%d", &n);
  printf("sign(%d) = %d\n", n, n == 0 ? 0 : (n > 0 ? 1 : -1));
  return 0;
}