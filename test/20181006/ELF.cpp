#include <iostream>
#include <stdio.h>
#define HE 201314
#define MAXN 100010
#define LOGMAXN 20
using namespace std;

int N, Q, fa[MAXN], P[MAXN][LOGMAXN], dep[MAXN], Log[MAXN];

void initLCA();
int LCA(const int&, const int&);

int main(){
    #ifdef DEBUG
    freopen("elf4.in", "r", stdin);
    freopen("elf.out", "w", stdout);
    #endif // DEBUG
    scanf("%d%d", &N, &Q);
    for (int i=1; i<N; i++){
        scanf("%d", &fa[i]);
        fa[i]--;
    }
    initLCA();
    dep[0]=1; for (int i=1; i<N; i++) dep[i]=dep[fa[i]]+1;
    for (int i=0; i<Q; i++){
        int l, r, z, ans=0;
        scanf("%d%d%d", &l, &r, &z);
        l--; r--; z--;
        for (int j=l; j<=r; j++) ans=(ans+dep[LCA(z, j)])%HE;
        printf("%d\n", ans);
    }
}

void initLCA(){
    for (int i=0; i<N; i++)
        for (int j=0; 1<<j<N; j++)
            P[i][j]-1;
    for (int i=0; i<N; i++) P[i][0]=fa[i];
    for (int j=1; 1<<j<N; j++) 
        for (int i=0; i<N; i++)
            if (P[i][j-1]!=-1) P[i][j]=P[P[i][j-1]][j-1];
}   

int LCA(const int& x, const int& y){
    int p=x, q=y, log;
    if (dep[p]<dep[q]) swap(p, q);
    if (Log[p]==0) {
        for (log=1; 1<<log<=dep[p]; log++); log--;
        Log[p]=log;
    }else log=Log[p];
    for (int i=log; i>=0; i--)
        if (dep[p]-(1<<i)>=dep[q])
            p=P[p][i];
    if (p==q) return p;
    for (int i=log; i>=0; i--)
        if (P[p][i]!=-1 && P[p][i]!=P[q][i]){
            p=P[p][i]; 
            q=P[q][i];
        }
    return fa[p];
}