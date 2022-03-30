#include <stdio.h>

int main(){
  int n, min = 0x7FFFFFFF;
  scanf("%d", &n);
  for (register int i = 0; i < n; i++){
    int a;
    scanf("%d", &a);
    if (a < min) min = a;
  }
  printf("min = %d\n", min);
  return 0;
}