#include <cstdio>

int solve(const int &n, const int &x){
  int sum = 0; 
  bool haveX = 0, allX = 1;
  for (register int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    sum += a;
    if (a == x) haveX = 1;
    if (a != x) allX = 0;
  }
  if (allX) return 0;
  if (n*x == sum) return 1;
  if (haveX) return 1;
  return 2;
}

int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    int n, x;
    scanf("%d%d", &n, &x);
    printf("%d\n", solve(n, x));
  }
}