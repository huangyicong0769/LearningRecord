#include <stdio.h>

struct Staff{
  char name[11];
  double ba, fl, ep;
}staff;

int main(){
  int n;
  scanf("%d", &n);
  struct Staff staff[n];
  for (register int i = 0; i < n; i++)
    scanf("%s %lf %lf %lf", (staff + i)->name, &(staff + i)->ba, &(staff + i)->fl, &(staff + i)->ep);
  for (register int i = 0; i < n; i++)
    printf("%s %.2lf\n", (staff + i)->name, (staff + i)->ba + (staff + i)->fl - (staff + i)->ep);
}