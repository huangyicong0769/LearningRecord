/*
    BZOJ 2252
    CH 2501
*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct Node{
    int x, y;
};

const int di[4][2]={{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

queue<Node> q;

char a[1010][1010];
int b[1010][1010], N, M;

int main(){
    memset(b, 0xFFFFFFFF, sizeof(b));
    scanf("%d%d\n", &N, &M);
    for (register int i=0; i<N; i++) scanf("%s", a[i]);
    for (register int i=0; i<N; i++) for (register int j=0; j<M; j++) if (a[i][j]=='1') q.push((Node){i, j}), b[i][j]=0;
    while (q.size()){
        Node now=q.front(); q.pop();
        for (register int d=0; d<4; d++) {
            Node nex;
            nex.x=now.x+di[d][0];
            nex.y=now.y+di[d][1];
            if (nex.x>=0 && nex.y>=0 && nex.x<N && nex.y<M && b[nex.x][nex.y]==-1) b[nex.x][nex.y]=b[now.x][now.y]+1, q.push(nex);
        }
    }
    for (register int i=0; i<N; i++) {
        for (register int j=0; j<M; j++) printf("%d ", b[i][j]);
        puts("");
    }
}