#include <stdio.h>

int main(){
  int N;
  scanf("%d", &N);
  for (register int i = 1; i <= N; i++){
    for (register int j = 1; j <= i; j++)
      printf("%d*%d=%-4.d", j, i, i*j);
    printf("\n");
  }  
  return 0;
}
