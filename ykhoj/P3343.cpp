#include <iostream>
#include <cstdio>
#include <algorithm>
#define reg register
#define f(a, b, c) for (reg int a=b; a<=c; a++)
using namespace std;

struct {int l, r, st; } qu[10010];

int a[20010], fa[20010], d[20010], N, M, T;

int get(int);

int main(){
    scanf("%d%d", &N, &M);
    f (i, 1, M){
        char str[5];
        scanf("%d%d%s", &qu[i].l, &qu[i].r, str);
        qu[i].st=(str[0]=='o' ? 1 :0);
        a[++T] = qu[i].l-1;
        a[++T] = qu[i].r;
    }
    sort(a+1, a+T+1);
    N=unique(a+1, a+T+1) - a - 1;
    f (i, 1, N) fa[i]=i;
    f (i, 1, M){
        reg int x = lower_bound(a+1, a+N+1, qu[i].l-1)-a,
                y = lower_bound(a+1, a+N+1, qu[i].r)-a,
                p=get(x), q=get(y);
        if (q==p){
            if ((d[x]^d[y])!=qu[i].st) {
                printf("%d\n", i-1);
                return 0;
            }
        }else{
            fa[q]=p;
            d[q]=d[x]^d[y]^qu[i].st;
        }
    }
    printf("%d\n", M);
}

int get(int x){
    if (fa[x]==x) return x;
    reg int r=get(fa[x]);
    d[x]^=d[fa[x]];
    return fa[x]=r;
}