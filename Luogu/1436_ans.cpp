//by Su Qingnian
//QAQ
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n;//n是总共切的刀数
int map[9][9];//存图，价值
int sum[9][9];//前缀和数组
int dp[9][9][9][9][15];//dp暴力数组
inline void add(int i,int j)
{
//这个函数是计算前缀和数组。左上(1,1)右下(i,j)的价值
//好好想想为什么。（扩展这个点时左边矩形+右边矩形-重叠的部分+这个点的价值）
    sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
    return ;
}
inline int s(int x1,int y1,int x2,int y2)
{
//这个是用来计算左上(x1,y1)右下(x2,y2)的价值
//还是容斥原理
    int now=sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
    return now;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=8;i++)
      for(int j=1;j<=8;j++)
      scanf("%d",&map[i][j]),
      add(i,j);//输入，处理前缀和

//debug
//  for(int i=1;i<=8;i++,puts(""))
//    for(int j=1;j<=8;j++)
//    printf("%-5d ",sum[i][j]); 
//处理切0刀时各矩形价值的平方
    for(int i=1;i<=8;i++)
     for(int j=1;j<=8;j++)
       for(int x=i;x<=8;x++)
         for(int y=j;y<=8;y++)
           dp[i][j][x][y][0]+=s(i,j,x,y),
           dp[i][j][x][y][0]*=dp[i][j][x][y][0];
//dp过程，深吸一口气读完这一面方程。
    for(int k=1;k<n;k++)
      for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
          for(int x=i;x<=8;x++)
            for(int y=j;y<=8;y++)
            {
                int minn=0x3f3f3f3f;
                for(int a=j;a<y;a++)
                  minn=min(minn,min(dp[i][j][x][a][k-1]+dp[i][a+1][x][y][0],dp[i][j][x][a][0]+dp[i][a+1][x][y][k-1]));
                for(int b=i;b<x;b++)
                  minn=min(minn,min(dp[i][j][b][y][k-1]+dp[b+1][j][x][y][0],dp[i][j][b][y][0]+dp[b+1][j][x][y][k-1]));
                dp[i][j][x][y][k]=minn;
            }
    printf("%d",dp[1][1][8][8][n-1]); 
 //输出，程序拜拜。
    return 0;
}