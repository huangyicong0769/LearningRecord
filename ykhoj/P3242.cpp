#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct Stuff{
    int p, d;
}stuffs[10100];

bool myComp(const Stuff&, const Stuff&);
inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N;
    while (scanf("%d", &N)!=EOF){
        for (int i=0; i<N; i++){
            stuffs[i].p=read();
            stuffs[i].d=read();
        }
        int ans=0;
        priority_queue<int> pq;
        sort(stuffs, stuffs+N, myComp);
        for (int i=0; i<N; i++){
            if (stuffs[i].d>pq.size()) {
                pq.push(stuffs[i].p*-1);
                ans+=stuffs[i].p;
            }
            else if (stuffs[i].d==pq.size() && stuffs[i].p*-1<pq.top()){
                ans+=pq.top();
                pq.pop();
                pq.push(stuffs[i].p*-1);
                ans+=stuffs[i].p;
            }
        }
        printf("%d\n", ans);
    }
}

bool myComp(const Stuff& a, const Stuff& b){
    return a.d<b.d;
}

inline int read(){
    int x=0, f=1; char ch=getchar();
    while (ch<'0' || ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}