#include <stdio.h>
#include <math.h>

int isPrime(int);

int main(){
  int N;
  scanf("%d", &N);
  for (register int i = 2; i <= N; i++)
    if (isPrime(i) && isPrime(N - i)) {
      printf("%d = %d + %d\n", N, i, N - i);
      break;
    }
  return 0;
}

int isPrime(int n){
  if (n == 1 || n == 0) return 0;
  double sqrtn = sqrt(n);
  for (register int j = 2; j <= sqrtn; j++)
    if (n % j == 0) return 0;
  return 1;
}
