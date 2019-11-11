#include <iostream>
#include <cstdio>
#include <queue>
#include <bitset>
#include <vector>
using namespace std;

vector<int> v[30010], topord; 
bitset<30000> b[30000];

int d[30010];

inline int read();
inline void topsort(const int &);

int main(){
    const int N=read(), M=read();
    for (register int i=0, x, y; i<M; i++){
        x=read(); y=read();
        v[x].push_back(y);
        d[y]++;
    } 
    topsort(N);
    for (register int i=N-1; i>0; i--){
        register int & t=topord[i];
        b[t][t]=1;
        for (register int j=0; j<v[t].size(); j++) b[t]|=b[v[t][j]];
    }
    for (register int i=0; i<N; i++)
        printf("%d\n", b[i].count());
}

inline int read(){
    int x=0, f=1; char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x*f;
}

inline void topsort(const int & N){
    queue<int> q;
    for (register int i=0; i<N; i++) if (d[i]==0) q.push(i);
    while (q.size()){
        register int x=q.front(); q.pop();
        topord.push_back(x);
        for (register int i=0; i<v[x].size(); i++) if (--d[v[x][i]]==0) q.push(v[x][i]); 
    }
}