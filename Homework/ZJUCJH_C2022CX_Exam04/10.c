#include <stdio.h>

int main() {
  int N;
  scanf("%d", &N);
  int n = N % 5;
  if (n > 0 && n < 4) printf("Fishing in day %d\n", N);
  else printf("Drying in day %d\n", N);
  return 0;
}