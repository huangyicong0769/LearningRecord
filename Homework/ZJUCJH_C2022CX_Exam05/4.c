#include <stdio.h>

int gcd (int, int);

int main(){
  int M, N;
  scanf("%d%d", &M, &N);
  if (N > M) {
    int t = N;
    N = M;
    M = t;
  }
  int g = gcd(M, N);
  printf("%d %d\n", g, M * N /g);
  return 0;
}

int gcd(int a, int b) {
  return b ? gcd(b, a %b) : a;
}