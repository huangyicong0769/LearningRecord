#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
using namespace std;

int team[1000100];

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int T=read(), cnt=1; 
    for (;1;T=read(), cnt++){
        if (T==0) break;
        queue<int> q[T+10];
        memset(team, 0, sizeof(team));
        for (int i=1; i<=T; i++){
            int N=read();
            for (int j=0; j<N; j++) {
                int a=read();
                team[a]=i;
            }
        }
        printf("Scenario #%d\n", cnt);
        string s; cin>>s;
        for (;1;cin>>s){
            if (s=="STOP") break;
            if (s=="ENQUEUE") {
                int a=read();
                if (q[team[a]].size()==0) q[0].push(team[a]);
                q[team[a]].push(a);
            }else if (s=="DEQUEUE"){
                int qf=q[0].front();
                printf("%d\n", q[qf].front());
                q[qf].pop();
                if (q[qf].size()==0) q[0].pop();
            }
        }
        printf("\n");
    }
}

inline int read(){
    int x=0, f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}