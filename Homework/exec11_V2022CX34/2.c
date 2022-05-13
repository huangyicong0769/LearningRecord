#include <stdio.h>

void input(const char *str, float *a){
    printf("%s", str);
    scanf("%f", a);
}

void splitfloat(float x, int *intpart, float *fracpart){
    *intpart = (int) x;
    *fracpart = x - *intpart;
}

int main(){
    float x, fracP;
    int intP;
    input("Enter x:", &x);
    splitfloat(x, &intP, &fracP);
    printf("The intpart is %d\nThe fracpart is %.6f\n", intP, fracP);
}