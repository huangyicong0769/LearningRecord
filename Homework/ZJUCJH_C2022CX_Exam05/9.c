#include <stdio.h>

int pow(int a, int n){
  if (n == 0) return 1;
  if (n == 1) return a;
  register int tmp = pow(a, n/2);
  tmp *= tmp;
  return n%2 ? tmp*a : tmp;
}

int main(){
  int N;
  scanf("%d", &N);
  int min = pow(10, N - 1), max = pow(10, N);
  for (register int i = min; i < max; i++){
    register int sum = 0, num = i;
    for (register int j = 0; j < N; j++){
      sum += pow(num%10, N);
      num /= 10;
      if (sum > i) break;
    }
    if (sum == i) printf("%d\n", i);
  }
  return 0;
}