#include <stdio.h>

int main(){
  int N;
  scanf("%d", &N);
  int cnt = 0;
  for (register int i = 0; i < N; i++){
    for (register int j = 0; j < N - i; j++)
      printf("%c ", 'A' + cnt++);
    printf("\n");
  }
}