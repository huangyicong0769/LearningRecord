#include <stdio.h>

int main(){
  int a, n, s = 0;
  printf("Enter a, n:"); scanf("%d%d", &a, &n);
  int tmp = 0;
  for (register int i = 0; i < n; i++){
    tmp = tmp * 10 + a;
    s += tmp;
  }
  printf("s=%d\n", s);
}