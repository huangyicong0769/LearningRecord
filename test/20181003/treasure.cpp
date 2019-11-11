#include <iostream>
#include <cstdio>
#define llMAX (1LL<<63)-1
using namespace std;

typedef long long ll;

ll map[20][20], f[(1<<12)-1][12];

bool bb[20][20];

int cnt(const int&);

int main(){
    freopen("treasure.in", "r", stdin);
    freopen("treasure.out", "w", stdout);
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i=0; i<M; i++){
        ll x, y, v;
        scanf("%lld%lld%lld", &x, &y, &v);
        x--; y--;
        if (bb[x][y]!=1){
            bb[x][y]=bb[y][x]=1;
            map[x][y]=map[y][x]=v;
        }else map[x][y]=map[y][x]=min(map[x][y], v);
    }
    for (int b=1; b<(1<<N); b++){
        int nb=cnt(b);
        if (nb==1) {
            for (int i=0; i<N; i++) if ((b>>i)&1) f[b][i]=0;
            continue;
        }
        for (int i=0; i<N; i++) if ((b>>i)&1){
            f[b][i]=llMAX;
            for (int j=0; j<N; j++) if ((b>>j)&1 && i!=j && bb[i][j]){
                f[b][i]=min(f[b][i], f[b^(1<<i)][j]+map[j][i]*(nb-1));
            }
        }
    }
    ll ans=llMAX;
    for (int i=0; i<N; i++) ans=min(ans, f[(1<<N)-1][i]);
    printf("%lld\n", ans);
    fclose(stdout);
}

int cnt (const int& B){
    int ans=0, t=B;
    while (t){
        if (t&1) ans++;
        t>>=1;
    }
    return ans;
}