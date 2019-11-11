#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

const int dir[4][2]={{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Point{
    int x, y;
};

int N, M, T, colors[50][50], tot=0;
bool sheet[50][50];
double ans=0;
queue<Point> q;

inline int readN();
inline void color(const int&, const int&);
void choose(int, const int&, const int&);

int main(){
    N=readN(), M=readN(), T=readN();
    char ch=getchar();
    for (int i=0; i<N; i++) for (int j=0; j<M; j++){
        while (ch<'0' || ch>'1') ch=getchar();
        sheet[i][j]=ch-'0';
        ch=getchar();
    }
    choose(T, 0, -1);
    printf("%.6lf", ans);
}

inline int readN(){
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

inline void color(const int& X, const int& Y){
    q.push((Point){X, Y});
    colors[X][Y]=++tot;
    while (!q.empty()){
        Point now=q.front(); q.pop();
        for (int d=0; d<4; d++){
            int nx=now.x+dir[d][0],
                ny=now.y+dir[d][1];
            if (nx>=0 && ny>=0 && nx<N && ny<M && !sheet[nx][ny] && colors[nx][ny]==0){
                colors[nx][ny]=tot;
                q.push((Point){nx, ny});
            }
        }
    }
}

void choose(int rest, const int& laX, const int& laY){
    if (rest==0){
        memset(colors, 0, sizeof(colors));
        tot=0;
        for (int i=0; i<N; i++) for (int j=0; j<M; j++) if (!sheet[i][j] && colors[i][j]==0) color(i, j);
        for (int x1=0; x1<N; x1++) for (int y1=0; y1<M; y1++) if (!sheet[x1][y1])
        for (int x2=x1; x2<N; x2++) for (int y2=(x1==x2)?(y1+1):0; y2<M; y2++) if (!sheet[x2][y2] && colors[x1][y1]==colors[x2][y2]) 
            ans=max(ans, sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))); 
        return;
    }
    for (int i=laX; i<N; i++) for (int j=(i==laX)?(laY+1):0; j<M; j++) if (sheet[i][j]){
        choose(rest, i, j);
        sheet[i][j]=0;
        choose(rest-1, i, j);
        sheet[i][j]=1;
    }
}