#include <stdio.h>

int a[15];

int main(){
  int n;
  scanf("%d", &n);
  for (register int i = 0; i < n; i++) scanf("%d", a+n-i-1);
  for (register int i = 0; i < n - 1; i++) printf("%d ", a[i]);
  printf("%d\n", a[n-1]);
}