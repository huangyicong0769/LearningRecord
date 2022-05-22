#include <stdio.h>
#include <math.h>

struct vector{
  double x, y;
};
typedef struct vector vector;

int main(){
  vector a, b;
  scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
  vector c = {a.x + b.x, a.y + b.y};
  if (fabs(c.x) < 0.05) c.x = fabs(c.x);
  if (fabs(c.y) < 0.05) c.y = fabs(c.y);
  printf("(%.1lf, %.1lf)\n", c.x, c.y);
}