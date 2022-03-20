#include <stdio.h>

double mypow( double x, int n );

int main()
{
    double x;
    int n;

    scanf("%lf %d", &x, &n);
    printf("%f\n", mypow(x, n));

    return 0;
}

/* 你的代码将被嵌在这里 */
double mypow( double x, int n ){
  if (n == 0) return 1;
  if (n == 1) return x;
  double tmp = mypow(x, n/2);
  return n%2 ? tmp*tmp*x : tmp*tmp;
}