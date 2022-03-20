#include <stdio.h>

int main() {
  int N, cout[5] = {0};
  scanf("%d", &N);
  for (register int i = 0; i < N; i++){
    int score;
    scanf("%d", &score);
    score -= 50;
    score /= 10;
    if (score < 0) score = 0;
    if (score > 4) score = 4;
    cout[score] ++;
  }
  for (register int i = 4; i > 0; i--) printf("%d ", cout[i]);
  printf("%d", cout[0]);
  return 0;
}