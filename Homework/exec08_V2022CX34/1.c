#include <stdio.h>
#include <math.h>

int isPrime(int);
int findPrime(int);

int main(){
  int cnt = 0;
  for (register int i = 6; i <= 100; i+=2){
    int pr = findPrime(i);
    printf("%3.d=%2.d+%-3.d ", i, pr, i - pr);
    if ((++cnt)%5 == 0) printf("\n");
  }  
}

int isPrime(int n){
  if (n == 1 || n == 0) return 0;
  double sqrtn = sqrt(n);
  for (register int j = 2; j <= sqrtn; j++)
    if (n % j == 0) return 0;
  return 1;
}

int findPrime(int n){
  for (register int i = 3; i <= n/2; i++)
    if (isPrime(i) && isPrime(n - i)) return i;
  return -1;
}