#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int di[4][2]={{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
const int nex[3][3][4]={{{0, 0, -2, 1}, {0, 0, -1, 1}, {0, 0, -1, 2}}, 
                       {{-2, 1, 0, 0}, {-1, 2, 0, 0}, {-1, 1, 0, 0}}, 
                       {{1, 1, 2, 2}, {0, 0, 1, 1}, {2, 2, 0, 0}}};

struct Node{
    int x, y, lie;
}st, ed;

queue<Node> q;

char m[510][510];
int d[505][505][3], N, M;

inline bool legal(const int &, const int &);
inline bool legal(const Node &);
inline void init();
inline int bfs();

int main(){
    for (scanf("%d%d", &N, &M); N && M ; scanf("%d%d", &N, &M)){
        for (register int i=0; i<N; i++) scanf("%s", m[i]);
        init();
        int ans=bfs();
        if (ans==-1) puts("Impossible"); else printf("%d\n", ans);
    }
}

inline bool legal(const int & x, const int & y){
    return x>=0 && y>=0 && x<N && y<M;
}

inline bool legal(const Node & a){
    if (!legal(a.x, a.y) ||
     (m[a.x][a.y]=='#') ||
     (a.lie==0 && m[a.x][a.y]!='.') ||
     (a.lie==1 && m[a.x][a.y+1]=='#') ||
     (a.lie==2 && m[a.x+1][a.y]=='#')) 
    return 0; 
    return 1;
}

inline void init(){
    for (register int i=0; i<N; i++) for (register int j=0; j<M; j++)
        if (m[i][j]=='O') ed.x=i, ed.y=j, m[i][j]='.';
        else if (m[i][j]=='X'){
            for (register int k=0; k<4; k++){
                int x=i+di[k][0], y=j+di[k][1];
                if (legal(x, y) && m[x][y]=='X'){
                    st.x=min(i, x),  st.y=min(j, y),
                    st.lie=k<2?1:2,
                    m[i][j]=m[x][y]='.';
                    break;
                }
            }
            if (m[i][j]=='X') st.x=i, st.y=j, st.lie=0;
        }
}

inline int bfs(){
    memset(d, 0xFFFFFFFF, sizeof(d));
    while (q.size()) q.pop();
    d[st.x][st.y][st.lie]=0; q.push(st);
    while (q.size()){
        Node now=q.front(); q.pop();
        for (register int dj=0; dj<4; dj++){
            Node tnex;
            tnex.x=now.x+nex[0][now.lie][dj];
            tnex.y=now.y+nex[1][now.lie][dj];
            tnex.lie=nex[2][now.lie][dj];
            if (legal(tnex) && d[tnex.x][tnex.y][tnex.lie]==-1){
                d[tnex.x][tnex.y][tnex.lie]=d[now.x][now.y][now.lie]+1;
                q.push(tnex);
                if (tnex.x==ed.x && tnex.y==ed.y && tnex.lie==ed.lie) return d[tnex.x][tnex.y][tnex.lie];
            }
        }
    }
    return -1;
}