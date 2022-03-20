#include <stdio.h>

int main() {
  int salary;
  printf("Enter salary:"); scanf("%d", &salary);
  double r;
  if (salary <= 1600) r = 0;
  else if (salary <= 2500) r = 0.05;
  else if (salary <= 3500) r = 0.1;
  else if (salary <= 4500) r = 0.15;
  else r = 0.2;
  printf("Tax = %.2lf\n", r*(salary - 1600));
  return 0;
}