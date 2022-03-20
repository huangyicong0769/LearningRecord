#include <stdio.h>

int main() {
  int FS, LS;
  scanf("%d%d", &FS, &LS);
  double rate = (FS - LS)*1.0 / LS;
  if (rate >= 0.5) printf("Exceed %.0lf%%. License Revoked\n", rate*100);
  else if (rate >= 0.1) printf("Exceed %.0lf%%. Ticket 200\n", rate*100);
  else printf("OK\n");
  return 0;
}