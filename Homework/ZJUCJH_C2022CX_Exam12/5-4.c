#include <stdio.h>

struct Book{
  char name[31];
  double price;
};

typedef struct Book Book;

void input(char *str){
  int n = 0;
  for (register char ch = getchar(); ch != '\n'; ch = getchar())
    str[n++] = ch;
  str[n] = '\0';
}

int main(){
  int n;
  scanf("%d", &n);getchar();
  Book books[n], *maxp = NULL, *minp = NULL;
  for (register int i = 0; i < n; i++){
    input(books[i].name);
    scanf("%lf", &books[i].price);getchar();
    if (maxp == NULL || maxp->price < books[i].price) maxp = books + i;
    if (minp == NULL || minp->price > books[i].price) minp = books + i;
  }
  printf("%.2lf, %s\n%.2lf, %s\n", maxp->price, maxp->name, minp->price, minp->name);
}