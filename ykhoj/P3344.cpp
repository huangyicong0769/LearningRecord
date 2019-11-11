#include <iostream>
#include <cstdio>
#define MAXN 50000
#define reg register
#define f(a, b, c) for (reg int a=b; a<c; a++)
#define cnt {++ans; continue; }
using namespace std;

int fa[3*MAXN+5];

int get(int x){
    if (fa[x]==x) return x;
    else return fa[x]=get(fa[x]);
}

int main(){
    int N, K, ans=0;
    scanf("%d%d", &N, &K);
    f (i, 1, 3*N+1) fa[i]=i;
    f (i, 0, K){
        int st, x, y;
        scanf("%d%d%d", &st, &x, &y);
        if (x>N || y>N || st==2 && x==y) cnt;
        if (st==1){
            if (get(x+N)==get(y) || get(x)==get(y+N)) cnt;
            fa[get(x)]=get(y);
            fa[get(x+N)]=get(y+N);
            fa[get(x+N+N)]=get(y+N+N);
        }else if (st==2){
            if (get(x)==get(y) || get(x)==get(y+N)) cnt;
            fa[get(x)]=get(y+N+N);
            fa[get(x+N)]=get(y);
            fa[get(x+N+N)]=get(y+N);
        }
    } 
    printf("%d\n", ans);
}