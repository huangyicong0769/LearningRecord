#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int N, M, S, T, K, f[1010];
vector<pair<int, int> > fd[1010], bd[1010]; 

inline int read();
inline void dijstra();
inline int bfs();

int main(){
    N=read(); M=read();
    for (register int i=0; i<M; i++){
        const int A=read(), B=read(), T=read();
        fd[A].push_back(make_pair(B, T));
        bd[B].push_back(make_pair(A, T));
    }
    S=read(); T=read(); K=read();
    dijstra();
    printf("%d\n", bfs());
}

inline int read(){
    int x=0; char ch;
    for (ch=getchar(); ch<'0' || ch>'9'; ch=getchar()) if (ch==EOF) return EOF;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x;
}

inline void dijstra(){
    bool b[1010]={0};
    memset(f, 0x3F, sizeof(f));
    priority_queue<pair<int, int> > pq;
    f[T]=0;
    pq.push(make_pair(0, T));
    for (;pq.size();){
        int x=pq.top().second;
        pq.pop();
        if (b[x]) continue;
        b[x]=1;
        for (register int i=0; i<bd[x].size(); i++){
            int y=bd[x][i].first, z=bd[x][i].second;
            if (f[y]>f[x]+z){
                f[y]=f[x]+z;
                pq.push(make_pair(-f[y], y));
            }
        }
    }
}

inline int bfs(){
    if (S==T) ++K;
    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(-f[S], S));
    int cnt[1010]={0};
    for (;pq.size();){
        int x=pq.top().second,
            di=-pq.top().first-f[x];
        pq.pop();
        ++cnt[x];
        if (cnt[T]==K) return di;
        for (register int i=0; i<fd[x].size(); i++) if (cnt[fd[x][i].first]<K) 
            pq.push(make_pair(-di-f[fd[x][i].first]-fd[x][i].second, fd[x][i].first));
    }
    return -1;
}