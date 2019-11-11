#include <iostream>
#include <cstdio>
#include <cmath>
#define reg register
#define f(a, b, c) for (reg int a=b; a<c; a++)
#define N 30000
using namespace std;

int fa[N+5], d[N+5], si[N+5], T;

int get(int);

int main(){
    f (i, 1, N) fa[i]=i, si[i]=1, d[i]=0;
    for (scanf("%d", &T); T; T--){
        char ch; int i, j;
        cin>>ch;
        cin>>i>>j;
        int x=get(i), y=get(j);
        if (ch=='M'){
            fa[x]=y;
            d[x]=si[y];
            si[y]+=si[x];
        }
        if (ch=='C'){
            if (x==y) printf("%d\n", abs(d[i]-d[j])-1);
            else puts("-1");
        }
    }
}

int get(int x){
    if (fa[x]==x) return x;
    reg int r=get(fa[x]);
    d[x]+=d[fa[x]];
    return fa[x]=r;
}
