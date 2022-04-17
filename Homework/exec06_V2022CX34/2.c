#include <stdio.h>

int f[105];

int fib(int n){
  if (f[n]) return f[n];
  if (n == 1 || n == 2) return f[n] = 1;
  return f[n] = fib(n - 1) + fib(n - 2);
}

int main(){
  int x;
  printf("Enter x: "); scanf("%d", &x);
  printf("fib(%d) = %d\n", x, fib(x));
}