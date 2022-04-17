#include <stdio.h>

int gcd(int a, int b){
  return b ? gcd(b, a%b) : a;
}

int lcm(int a, int b){
  return a*b/gcd(a, b);
}

int main(){
  int m, n;
  printf("Enter m, n: "); scanf("%d%d", &m, &n);
  printf("gcd = %d\nlcm = %d\n", gcd(m, n), lcm(m, n));
  return 0;
}