#include <stdio.h>

struct Time{
  int h, m, s;
};

int main(){
  struct Time ti;;
  scanf("%d:%d:%d", &ti.h, &ti.m, &ti.s);
  int n;
  scanf("%d", &n);
  ti.s += n;
  ti.m += ti.s/60;
  ti.s %= 60;
  ti.h += ti.m/60;
  ti.m %= 60;
  ti.h %= 24;
  if (ti.h < 10) printf("0");
  printf("%d:", ti.h);
  if (ti.m < 10) printf("0");
  printf("%d:", ti.m);
  if (ti.s < 10) printf("0");
  printf("%d\n", ti.s);
}