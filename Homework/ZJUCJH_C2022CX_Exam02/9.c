#include <stdio.h>

inline int read(){
  int re = 0;
  for (register ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) re = re*10 + ch - '0';
  return re;
}

int main(){
  int f;
  scanf("%d", &f);
  printf("Celsius = %d\n", 5*(f - 32)/9);
  return 0;
}