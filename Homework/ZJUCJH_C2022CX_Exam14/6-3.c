#include <stdio.h>

int main(){
    double x;
    scanf("%lf", &x);
    printf("f(%.1lf) = %.1lf\n", x, x ? 1.0/x : 0.0);
}