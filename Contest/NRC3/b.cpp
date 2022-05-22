#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

vector<int> edge[300001];
int color[300001];
int n, k;

void dfs(int x){
}

int main(){
  scanf("%d%d", &n, &k);
  for (register int i = 0; i < n - 1; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    edge[a].push_back(b);
    edge[b].push_back(a);
  }
  dfs(1); 
  if (k > 0) printf("-1");
  else for (register int i = 1; i <= n; i++) if (color[i]) printf("%d ", i);
  printf("\n");
}