#include <iostream>
#include <cstdio>
#include <algorithm>
#define reg register
#define f(a, b, c) for (reg int a=b; a<c; a++)
using namespace std;

int fa[10010];
pair<int, int> a[10010];

int getfa(int x){
    if (fa[x]==x) return x;
    else return fa[x]=getfa(fa[x]);
}

int main(){
    int N;
    while (~scanf("%d", &N)){
        int D=0;
        f(i, 0, N) scanf("%d %d", &a[i].first, &a[i].second), D=max(D, a[i].second);
        sort(a, a+N);
        f(i, 0, D+1) fa[i]=i;
        int ans=0;
        for (reg int i=N-1; i>=0; i--){
            int x=getfa(a[i].second);
            if (x){
                ans+=a[i].first;
                fa[x]=x-1;
            }
        }
        printf("%d\n", ans);
    }
}