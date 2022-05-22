#include <stdio.h>

struct Student{
  char id[7], name[13];
  int s;
};
typedef struct Student Student;

int main(){
  int n;
  scanf("%d", &n);
  Student maxS;
  for (register int i = 0; i < n; i++){
    Student x;
    int s1, s2, s3;
    scanf("%s%s%d%d%d" ,x.id, x.name, &s1, &s2, &s3);
    x.s = s1 + s2 + s3;
    if (i == 0 || maxS.s < x.s) maxS = x;
  }
  printf("%s %s %d\n", maxS.name, maxS.id, maxS.s);
}