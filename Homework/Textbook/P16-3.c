#include <stdio.h>

int main() {
   int ans = 0;
   for (register int i = 0; i <= 100; i++) ans += (i%6 ? 0 : i);
   printf("%d\n", ans);
   return 0;
}