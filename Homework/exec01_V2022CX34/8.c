#include <stdio.h>

int main() {
   register int ans = 0;
   for (register int i = 0; i <= 100; i++) ans += (i%2 ? 0 : i);
   printf("%d\n", ans);
   return 0;
}