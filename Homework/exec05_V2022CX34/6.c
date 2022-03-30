#include <stdio.h>

int main(){
  int n, m = 0, s = 0, f1 = 0, f2 = 1;
  printf("Enter n:"); scanf("%d", &n);
  while (s < n) {
    m++;
    s = f1 + f2;
    f1 = f2;
    f2 = s;
  }
  if (n > 1) m++;
  printf("m=%d\n", m);
}