#include <stdio.h>

int narcissistic( int number );
void PrintN( int m, int n );
    
int main()
{
    int m, n;
  
    scanf("%d %d", &m, &n);
    if ( narcissistic(m) ) printf("%d is a narcissistic number\n", m);
    PrintN(m, n);
    if ( narcissistic(n) ) printf("%d is a narcissistic number\n", n);

    return 0;
}

/* 你的代码将被嵌在这里 */
int pow(int a, int n) {
  int ans = 1;
  for (register int i = 0; i < n; i++) ans *= a;
  return ans;
}

int narcissistic( int number ){
  int cnt = 0, tmp = number;
  do{
    cnt++;
    tmp /= 10;
  }while (tmp);
  int dig = cnt;
  tmp = number;
  cnt = 0;
  do{
    cnt += pow((tmp % 10), dig);
    tmp /= 10;
  }while (tmp);
  return (cnt == number);
}

void PrintN( int m, int n ){
  for (register int i = m + 1; i < n; i++) 
    if (narcissistic(i)) printf("%d\n", i);
}
