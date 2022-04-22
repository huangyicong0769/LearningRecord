#include <stdio.h>
#include <math.h>

int search( int n );

int main()
{
    int number;

    scanf("%d",&number);
    printf("count=%d\n",search(number));
        
    return 0;
}


/* 你的代码将被嵌在这里 */
int search( int n ){
  int ret = 0;
  for (register int i = 10; i < 32; i++){
    if (i*i > n) break;
    int cnt[10] = {0},
        t = i*i;
    while (t != 0){
      cnt[t%10]++;
      t/=10;
    }
    for (register int j = 0; j < 10; j++)
      if (cnt[j] >= 2) {
        ret ++;
        break;
      }
  }
  return ret;
}