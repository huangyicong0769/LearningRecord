#include <stdio.h>

int fn( int a, int n );
int SumA( int a, int n );
    
int main()
{
    int a, n;

    scanf("%d %d", &a, &n);
    printf("fn(%d, %d) = %d\n", a, n, fn(a,n));        
    printf("s = %d\n", SumA(a,n));    
    
    return 0;
}

/* 你的代码将被嵌在这里 */
int fn(int a, int n){
  int ret = a;
  for (register int i = 1; i < n; i++){
    ret *= 10;
    ret += a;
  }
  return ret;
}

int SumA(int a, int n){
  int sum = 0;
  for (register int i = 1; i <= n; i++)
    sum += fn(a, i);
  return sum;
}