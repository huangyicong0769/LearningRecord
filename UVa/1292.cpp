#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#define SIZE 1506
#define reg register
#define f(i, s, t) for (reg int i=s; i!=t; i++)
using namespace std;

bool been[SIZE];
int N, f[SIZE], g[SIZE];
vector<int> w[SIZE];

void dp(int x){
  been[x]=1;
  f[x]=1, g[x]=0;
  f(i, 0, w[x].size()){
    reg int y=w[x][i];
    if (been[y]) continue;
    dp(y);
    f[x]+=min(f[y], g[y]);
    g[x]+=f[y];
  }
}

int main(){
  while(~scanf("%d", &N)){
    f(i, 0, N) {
      reg int a, b;
      scanf("%d:(%d)", &a, &b);
      f(j, 0, b) {
        reg int t;
        scanf("%d", &t);
        w[a].push_back(t), w[t].push_back(a);
      }
    }
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(been, 0, sizeof(been));
    dp(0);
    printf("%d\n", min(f[0], g[0]));
    f(i, 0, N) w[i].clear();
  }
}