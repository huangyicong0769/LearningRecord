#include <iostream>
#include <cstdio>
using namespace std;

int map[1010][1010];

int main(){
    freopen("phalanx.in", "r", stdin);
    freopen("phalanx.out", "w", stdout);
    int N, M, Q;
    scanf("%d%d%d", &N, &M, &Q);
    if (N==1){
        
    }else if (N>=1000 && M>=1000) printf("别想了， 我搞不定的:)\n");
    for (int i=0; i<N; i++) for (int j=0; j<M; j++) map[i][j]=M*i+j;
    while (Q--){
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        printf("%d\n", map[x][y]+1);
        int t=map[x][y];
        for (int i=y; i<M-1; i++) map[x][i]=map[x][i+1];
        for (int i=x; i<N-1; i++) map[i][M-1]=map[i+1][M-1];
        map[N-1][M-1]=t;
    }
}