/*
    POJ3635
*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct Node{
    int c, f, v;
    bool operator<(const Node&)const;
};

vector<int> V1[1010], V2[1010];

int d[1010][105], P[1010], N, M;

inline int read();
inline int bfs(const int , const int, const int);

int main(){
    N=read();
    M=read();
    for (register int i=0; i<N; i++) P[i]=read();
    for (register int i=0; i<M; i++){
        int x=read(), y=read(), v=read();
        V1[x].push_back(y); V2[x].push_back(v);
        V1[y].push_back(x); V2[y].push_back(v);
    }
    for (int Q=read(); Q; Q--){
        const int C=read(), S=read(), T=read();
        int ans=bfs(C, S, T);
        if (ans==-1) puts("impossible");
        else printf("%d\n", ans);
    }
}

bool Node::operator<(const Node& that)const{
    return this->v>that.v || this->v==that.v && this->f<that.f;
}

inline int read(){
    int x=0; char ch; 
    for (ch=getchar(); ch<'0' || ch>'9'; ch=getchar()) if (ch==EOF) return EOF;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x;
}

// inline int read(){
//     int x=0, f=1; char ch=getchar();
//     while (ch<'0' || ch>'9') {
//         if (ch=='-') f=-1;
//         ch=getchar();
//     }
//     while (ch>='0' && ch<='9') {
//         x=x*10+ch-'0';
//         ch=getchar();
//     }
//     return x*f;
// }

inline int bfs(const int C, const int S, const int T){
    // printf("#%d %d %d\n", C, S, T);
    priority_queue<Node> pq;
    memset(d, 0x7F, sizeof(d));
    pq.push((Node){S, 0, 0});
    d[S][0]=0;
    while (pq.size()){
        Node now=pq.top(); pq.pop();
        // printf("%d %d\n", now.c, now.f);
        if (now.c==T) return now.v;
        if (now.v>d[now.c][now.f]) continue;
        if (now.f<C && d[now.c][now.f+1]>now.v+P[now.c]){
            d[now.c][now.f+1]=now.v+P[now.c];
            pq.push((Node){now.c, now.f+1, now.v+P[now.c]}); 
        }
        for (register int i=0; i<V1[now.c].size(); i++){
            if (V2[now.c][i]<=now.f && d[V1[now.c][i]][now.f-V2[now.c][i]]>now.v){
                d[V1[now.c][i]][now.f-V2[now.c][i]]=now.v;
                pq.push((Node){V1[now.c][i], now.f-V2[now.c][i], now.v});
            }
        }
    }
    // for (int i=0; i<N; i++) {
    //     for (int j=0; j<C; j++) printf("%d ", d[i][j]); printf("\n");
    // }
    return -1;
}
