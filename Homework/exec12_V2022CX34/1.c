#include <stdio.h>

struct Student{
  int id;
  char name[10];
  double score;
};

typedef struct Student Student;

int main(){
  int n;
  scanf("%d", &n);
  Student stus[n];
  double sumScore = 0;
  for (register int i = 0; i < n; i++){
    scanf("%d%s%lf", &stus[i].id, stus[i].name, &stus[i].score);
    sumScore += stus[i].score;
  }
  printf("%.2lf\n", sumScore/n);
}