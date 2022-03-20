#include <stdio.h>

int fact(int n){
  register int re = 1;
  for(register int i= 1; i <= n; i++) re *= i;
  return re;
}

int main(){
  int N;
  scanf("%d", &N);
  int sum = 0;
  for (register int i = 1; i <= N; i++) sum += fact(i);
  printf("%d\n", sum);
}