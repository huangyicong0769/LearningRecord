#include <stdio.h>

int main(){
  int a[3];
  for (register int i = 0; i < 3; i++) scanf("%d", &a[i]);
  for (register int i = 0; i < 3; i++) 
    for (register int j = i + 1; j < 3; j++) 
      if (a[i] > a[j]) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      }
  printf("%d->%d->%d\n", a[0], a[1], a[2]);
  return 0;
}