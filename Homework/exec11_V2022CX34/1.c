#include <stdio.h>

void input(const char *str, float *a, float *b){
    printf("%s", str);
    scanf("%f%f", a, b);
}

void sum_diff(float op1, float op2, float *psum, float *pdiff){
    *psum = op1 + op2;
    *pdiff = op1 - op2;
}

int main(){
    float x, y, sum, diff;
    input("Enter x, y:", &x, &y);
    sum_diff(x, y, &sum, &diff);
    printf("The sum is %.2lf\nThe diff is %.2lf\n", sum, diff);
}