#include <stdio.h>

#define MAXN 10

double f( int n, double a[], double x );

int main()
{
    int n, i;
    double a[MAXN], x;
    
    scanf("%d %lf", &n, &x);
    for ( i=0; i<=n; i++ )
        scanf("%lf", &a[i]);
    printf("%.1f\n", f(n, a, x));
    return 0;
}

/* 你的代码将被嵌在这里 */

double pow(double x, int n){
    if (n == 0) return 1;
    if (n == 1) return x;
    double tmp = pow(x, n/2);
    return (n%2 ? tmp*tmp*x : tmp*tmp);
}

double f(int n, double a[], double x ){
    double sum = 0;
    for (register int i = 0; i <= n; i++)
        sum += a[i] * pow(x, i);
    return sum;
}
