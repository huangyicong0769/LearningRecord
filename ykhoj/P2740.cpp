#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int N, l, r;
    scanf("%d%d", &N, &l);
    r=l;
    long long ans=0;
    for (int i=0; i<N; i++) {
        int nx, ny;
        scanf("%d%d", &nx, &ny);
        if (nx<=l && r<=ny) continue;
        if (ny<l){
            ans+=l-ny;
            r=l;
            l=ny;
        }else
        if (nx>r){
            ans+=nx-r;
            l=r;
            r=nx;
        }else
        {
            l=max(l, nx);
            r=min(r, ny);
        }
        #ifdef DEBUG
        printf("%d %d %lld\n", l, r, ans);
        #endif // DEBUG
    }
    printf("%lld\n", ans);
}