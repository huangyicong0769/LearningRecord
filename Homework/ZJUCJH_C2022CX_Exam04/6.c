#include <stdio.h>

double price[105], rate[129];

int main() {
  price[90] = 6.95;
  price[93] = 7.44;
  price[97] = 7.93;
  rate['m'] = 0.95;
  rate['e'] = 0.97;
  int a, b;
  char ch;
  scanf("%d %d %c", &a, &b, &ch);
  printf("%.2lf\n", price[b]*a*rate[ch]);
  return 0;
}