#include <iostream>
#include <cstdio>
#include <deque>
#include <cstring>
using namespace std;

const int diret[4][2]={{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

struct Point{
    int x, y, ti;
};

int form[510][510][4];
bool bQ[600][600];

int main(){
    //freopen("input.txt", "r", stdin);
    int T;
    for (scanf("%d", &T); T; T--){
    memset(bQ, 0, sizeof(bQ));
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++){
            char c=0;
            while (c!='/' && c!='\\') scanf("%c", &c);
            //printf("%d %d %c\n", i, j, c);
            if (c=='/'){
                form[i][j][2]=form[i+1][j+1][3]=1;
                form[i+1][j][1]=form[i][j+1][0]=0;
            }else if (c=='\\'){
                form[i][j][2]=form[i+1][j+1][3]=0;
                form[i+1][j][1]=form[i][j+1][0]=1;
            }
        }
    bool done=0;
    deque<Point> dq;
    dq.push_back((Point){0, 0, 0});
    while (!dq.empty() && !done){
        Point now=dq.front(); dq.pop_front();
        if (bQ[now.x][now.y]) continue;
        bQ[now.x][now.y]=1;
        //printf("====\n%d %d %d\n", now.x, now.y, now.ti);
        for (int d=0; d<4; d++){
            int nx=now.x+diret[d][0],
                ny=now.y+diret[d][1];
            if (nx>=0 && nx<=N && ny>=0 && ny<=M){
                //printf("  %d %d %d %d\n", nx, ny, d, form[now.x][now.y][d]);
                Point t={nx, ny, now.ti};
                if (form[now.x][now.y][d]) {
                    t.ti++;
                    dq.push_back(t);
                }else dq.push_front(t);
                if (nx==N && ny==M) {
                    printf("%d\n", t.ti);
                    done=1;
                    break;
                }
            }
        }
    }
    if (!done) printf("NO SOLUTION\n");
    }
}