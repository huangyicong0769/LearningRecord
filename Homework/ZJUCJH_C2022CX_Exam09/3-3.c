#include <stdio.h>

struct Complex{
  double r, i;
}c1, c2;

struct Complex add(struct Complex a, struct Complex b){
  return (struct Complex) {a.r + b.r, a.i + b.i};
}
struct Complex mul(struct Complex a, struct Complex b){
  return (struct Complex) {a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r};
}

int main(){
  scanf("%lf%lf%lf%lf", &c1.r, &c1.i, &c2.r, &c2.i);
  struct Complex c3 = add(c1, c2), 
                 c4 = mul(c1, c2);
  printf("addition of complex is %.6lf+%.6lfi\nproduct of complex is %.6lf+%.6lfi\n", c3.r, c3.i, c4.r, c4.i);
}