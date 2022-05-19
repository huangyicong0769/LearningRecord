#include <stdio.h>
#define MAXN 10

struct student{
    int num;
    char name[20];
    int score;
    char grade;
};

int set_grade( struct student *p, int n );

int main()
{   struct student stu[MAXN], *ptr;
    int n, i, count;
    
    ptr = stu;
    scanf("%d\n", &n);
    for(i = 0; i < n; i++){
       scanf("%d%s%d", &stu[i].num, stu[i].name, &stu[i].score);
    } 
   count = set_grade(ptr, n);
   printf("The count for failed (<60): %d\n", count);
   printf("The grades:\n"); 
   for(i = 0; i < n; i++)
       printf("%d %s %c\n", stu[i].num, stu[i].name, stu[i].grade);
    return 0;
}

/* 你的代码将被嵌在这里 */
int set_grade( struct student *p, int n ){
  int cnt = 0;
  for (register int i = 0; i < n; i++){
    int score = (p + i)->score;
    char *grade = &(p + i)->grade;
    if (score >= 85) *grade = 'A';
    else if (score >= 70) *grade = 'B';
    else if (score >= 60) *grade = 'C';
    else {
      *grade = 'D';
      cnt++;
    }
  }
  return cnt;
}