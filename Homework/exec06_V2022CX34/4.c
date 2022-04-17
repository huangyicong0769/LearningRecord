#include <stdio.h>

double fact(int n){
  double ans = 1;
  for (register int i = 1; i <= n; i++) ans *= i;
  return ans;
}

double pow(double a, int n){
  if (n == 0) return 1;
  if (n == 1) return a;
  double tmp = pow(a, n/2);
  return tmp*tmp*pow(a, n%2);
}

double funCos(double eps, double x){
  double ans = 0, item;
  int i = 0, sign = 1;
  do{
    item = pow(x, i) / fact(i);
    ans += item * sign;
    sign *= -1; 
    i += 2;
  }while (item >= eps);
  // printf("%lf\n", item);
  return ans;
}

int main(){
  double eps, x;
  printf("Enter eps: "); scanf("%lf", &eps);
  printf("Enter x: "); scanf("%lf", &x);
  printf("cos(%lf) = %lf\n", x, funCos(eps, x));
  return 0;
}