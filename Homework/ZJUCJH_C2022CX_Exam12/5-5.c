#include <stdio.h>

struct frac{
  int m, d;
};
typedef struct frac frac;

int main(){
  frac a, b;
  scanf("%d/%d %d/%d", &a.m, &a.d, &b.m, &b.d);
  printf("%d/%d ", a.m, a.d);
  if (a.m*b.d > b.m*a.d) printf(">");
  if (a.m*b.d == b.m*a.d) printf("=");
  if (a.m*b.d < b.m*a.d) printf("<");
  printf(" %d/%d\n", b.m, b.d);
}