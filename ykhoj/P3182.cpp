#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node{
    int v, p;
}c[251];

int w[251][251], f[251][251];

bool comp(const Node& a, const Node& b){
    return a.v<b.v;
}

int main(){
    //freopen("input.txt", "r", stdin);
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    for (int i=1; i<=N; i++){
        scanf("%d", &c[i].v);
        c[i].p=i;
    }
    memset(w, 0x3F, sizeof(w));
    memset(f, 0x3F, sizeof(f));
    const int MAX=f[0][0];
    for (int i=1; i<=N; i++) f[i][i]=c[i].v;
    sort(c+1, c+N+1, comp);
    for (int i=0; i<M; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        w[a][b]=w[b][a]=min(w[a][b], c);
    }
    for (int k=1; k<=N; k++){
        for (int i=1; i<=N; i++)
            for (int j=1; j<=N; j++){
                int tk=c[k].p, ti=c[i].p, tj=c[j].p;
                //if (w[ti][tj]==MAX || w[ti][tk]==MAX || w[tk][tj]==MAX) continue;
                w[ti][tj]=w[tj][ti]=min(w[ti][tj], w[ti][tk]+w[tk][tj]);
                f[ti][tj]=f[tj][ti]=min(f[ti][tj], max(c[i].v, max(c[j].v, c[k].v))+w[ti][tj]);
            }
    }
    for (int i=0; i<K; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", f[x][y]);
    }
}