#include <stdio.h>

void pyramid( int n );

int main()
{    
    int n;

    scanf("%d", &n);
    pyramid(n);
    
    return 0;
}

/* 你的代码将被嵌在这里 */
void pyramid(int N){
  for (register int i = 1; i <= N; i++){
    for (register int j = 0; j < N - i; j++) putchar(' ');
    for (register int j = 0; j < i; j ++) printf("%d ", i);
    putchar('\n');
  }
}