#include <stdio.h>

int main(){
  int n;
  printf("Enter n: "); scanf("%d", &n);
  int tmp = 1;
  for (register int i = 0; i <= n; i++, tmp *= 3) 
    printf("pow(3, %d)=%d\n", i, tmp);
}