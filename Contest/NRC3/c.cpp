#include <cstdio>

int main(){
  int n;
  scanf("%d", &n); getchar();
  for (register int i = 0; i < n; i++){
    bool haveZero = 0, haveEven = 0;
    int sum = 0;
    for (register char ch = getchar(); ch != '\n'; ch = getchar()){
      int x = ch - '0';
      if (x == 0 && haveZero || x != 0 && x % 2 == 0) haveEven = 1; 
      if (x == 0 && !haveZero) haveZero = 1;
      sum += x;
    }
    if (sum == 0 || haveZero && haveEven && sum % 3 == 0) puts("red");
    else puts("cyan");
  }
}