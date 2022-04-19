#include <stdio.h>

int main(){
  int n;
  scanf("%d", &n);
  double sum = 0, a = 2, b = 1;
  while(n--){
    sum += (double)a / (double)b;
    double t = a;
    a += b;
    b = t;
    // printf("%d/%d %.2lf\n", a, b, sum);
  }
  printf("%.2lf\n", sum);
}