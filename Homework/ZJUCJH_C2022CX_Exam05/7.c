#include <stdio.h>

int main(){
  int x, cnt = 0;
  scanf("%d", &x);
  for (register int i = x/5; i > 0 ; i--) 
    for (register int j = x/2; j > 0; j--)
      for (register int k = x; k > 0; k--)
        if (5*i + 2*j + k == x) {
          cnt++;
          printf("fen5:%d, fen2:%d, fen1:%d, total:%d\n", i, j, k, i+j+k);
        }
  printf("count = %d\n", cnt);
  return 0;
}