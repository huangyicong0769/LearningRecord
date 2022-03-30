#include<stdio.h>
#include<math.h>
double fact(int(n)){
 int i;
 double product;
 product=1;
 for(i=1;i<=n;i++){
  product=product*i;
 }
 return product;
}
int main (void)
{
 int i;
 double x,sum,item;
 sum=1;
 i=1;
 scanf("%lf",&x);
 item=1;
 do{
  item=(item*x)/fact(i);
  sum=sum+item;
  i=i+1;
 }while(fabs(item)>=0.00001);
 printf("%.4f",sum);
 return 0;
 
}