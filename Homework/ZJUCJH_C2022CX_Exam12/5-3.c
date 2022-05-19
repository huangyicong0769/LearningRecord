#include <stdio.h>

struct Student{
  char ID[6], name[11];
  int score;
};

typedef struct Student Student;

int main(){
  int n;
  scanf("%d", &n);
  Student stu[n];
  int sum = 0;
  for (register int i = 0; i < n; i++) {
    scanf("%s%s%d", (stu + i)->ID, (stu + i)->name, &(stu + i)->score);
    sum += (stu + i)->score;
  }
  printf("%.2lf\n", (double)sum/n);
  for (register int i = 0; i < n; i++) 
    if (n*(stu + i)->score < sum)
      printf("%s %s\n", (stu + i)->name, (stu + i)->ID);
}