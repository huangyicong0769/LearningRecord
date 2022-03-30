#include <stdio.h>

int main(){
  int ANS, N;
  scanf("%d%d", &ANS, &N);
  for (register int i = 0; i < N; i++) {
    int g;
    scanf("%d", &g);
    if (ANS == g) {
      if (i == 0) printf("Bingo!\n");
      else if (i < 3) printf("Lucky You!\n");
      else printf("Good Guess!\n");
      break;
    }
    if (g < 0) {printf("Game Over\n"); break;}
    if (g > ANS) printf("Too big\n");
    if (g < ANS) printf("Too small\n");
    if (i == N - 1) printf("Game Over\n");
  }
  return 0;
}