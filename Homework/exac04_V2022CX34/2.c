#include <stdio.h>

int main() {
  int N, cout[5] = {0};
  scanf("%d", &N);
  for (register int i = 0; i < N; i++){
    int score;
    scanf("%d", &score);
    score -= 50;
    score /= 10;
    int tmp = 0;
    switch (score) {
      case 5: case 4:
        tmp++;
      case 3:
        tmp++;
      case 2:
        tmp++;
      case 1:
        tmp++;
    }
    cout[tmp] ++;
  }
  for (register int i = 4; i > 0; i--) printf("%d ", cout[i]);
  printf("%d\n", cout[0]);
  return 0;
}