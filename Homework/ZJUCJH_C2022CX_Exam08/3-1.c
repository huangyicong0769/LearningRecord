#include <stdio.h>

int main(){
  int n1, n2;
  scanf("%d", &n1);
  for (register char ch = getchar(); ch != '='; ch = getchar()){
    scanf("%d", &n2);
    switch (ch){
      case '+':
        n1 += n2;
        break;

      case '-':
        n1 -= n2;
        break;
          
      case '*':
        n1 *= n2;
        break;

      case '/':
        if (n2 == 0) goto Error;
        n1 /= n2;
        break;

      default:
        goto Error;
    }
  }
  printf("%d\n", n1);
  return 0;
Error:
  printf("ERROR");
  return 0;
}