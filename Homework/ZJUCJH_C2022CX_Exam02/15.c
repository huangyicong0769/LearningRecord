#include <stdio.h>

int main(){
  int a, b, h1, m1, h2, m2;
  scanf("%d%d", &a, &b);
  h1 = a/100;
  m1 = a%100;
  h2 = b/100;
  m2 = b%100;
  m2 -= m1;
  h2 -= h1;
  while (m2 < 0) {
    m2 += 60;
    h2--;
  }
  if (h2 < 10) printf("0");
  printf("%d:", h2);
  if (m2 < 10) printf("0");
  printf("%d\n", m2);
  return 0;
}