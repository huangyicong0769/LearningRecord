#include <stdio.h>

int main(){
  int n = 152;
  printf("%d=%d+%d*10+%d*100\n", n, n%10, n/10%10, n/100);
}