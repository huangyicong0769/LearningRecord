#include <stdio.h>

int main() {
  int N, cout[5] = {0};
  scanf("%d", &N);
  for (register int i = 0; i < N; i++){
    int score;
    scanf("%d", &score);
    if (score >= 90) cout[4]++;
    else if (score >= 80) cout[3]++;
    else if (score >= 70) cout[2]++;
    else if (score >= 60) cout[1]++;
    else cout[0]++;
  }
  for (register int i = 4; i > 0; i--) printf("%d ", cout[i]);
  printf("%d\n", cout[0]);
  return 0;
}