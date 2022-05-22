#include <stdio.h>

struct Person{
  char phone[23], name[13];
  int birth;
};
typedef struct Person Person;

int main(){
  int n;
  scanf("%d", &n);
  Person a[n + 3];
  for (register int i = 0; i < n; i++)
    scanf("%s %d %s", a[i].name, &a[i].birth, a[i].phone);
  for (register int i = 0; i < n; i++)
    for (register int j = i + 1; j < n; j++)
      if (a[i].birth > a[j].birth){
        Person tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      }
  for (register int i = 0; i < n; i++)
    printf("%s %d %s\n", a[i].name, a[i].birth, a[i].phone);
}