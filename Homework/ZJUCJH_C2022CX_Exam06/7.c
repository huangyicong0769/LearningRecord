#include <stdio.h>

int fib( int n );
void PrintFN( int m, int n );
    
int main()
{
    int m, n, t;

    scanf("%d %d %d", &m, &n, &t);
    printf("fib(%d) = %d\n", t, fib(t));
    PrintFN(m, n);

    return 0;
}

/* 你的代码将被嵌在这里 */
double pow(double a, int n) {
  if (n == 0) return 0;
  if (n == 1) return a;
  double tmp = pow(a, n /2);
  tmp *= tmp;
  return (n % 2 ? tmp*a : tmp); 
}

int fib( int n ){
  static double magicNum = 2.2360679775;
  return (int)((pow((1+magicNum)/2, n) - pow((1 - magicNum)/2, n))/ magicNum);
}

void PrintFN( int m, int n ){
  int haveFN = 0;
  for (register int i = 1; 1; i++){
    int tmp = fib(i);
    if (tmp < m) continue;
    if (tmp > n) break;
    if (haveFN) printf(" %d", tmp);
    else {
      haveFN = 1;
      printf("%d", tmp);
    }
  }
  if (haveFN == 0) printf("No Fibonacci number");
  putchar('\n');
}