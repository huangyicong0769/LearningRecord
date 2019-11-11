#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int N, W, ans=0x7FFFFFFF, C[20], cab[20];

inline int read();
void dfs(int, int);

int main(){
    N=read();
    W=read();
    for (int i=0; i<N; i++) C[i]=read()*-1;
    sort (C, C+N);
    dfs(0, 0);
    printf("%d\n", ans);
}

inline int read(){
    int x=0, f=1; char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x*f;
}

void dfs(int catid, int cabid){ 
    if (catid==N) ans=cabid;
    else{
        for (register int i=0; i<cabid; i++)
            if (cab[i]-C[catid]<=W) {
                cab[i]-=C[catid];
                dfs(catid+1, cabid);
                cab[i]+=C[catid];
            }
        if (cabid<ans){
            cab[cabid]-=C[catid];
            dfs(catid+1, cabid+1);
            cab[cabid]+=C[catid];
        }
    }
}