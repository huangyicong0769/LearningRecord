#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node{
    int p, d;
}a[20010];

int ans;

priority_queue<int> pq;

inline int read();
bool myComp(const Node&, const Node&);

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    const int N=read();
    for (register int i=0; i<N; i++){
        a[i].p=read();
        a[i].d=read();
    }
    sort(a, a+N, myComp);
    for (register int i=0; i<N; i++){
        if (i==0 || a[i].d!=a[i-1].d){
            for (register int t=a[i].d+1; pq.size() && t<a[i-1].d; t++){
                ans+=pq.top();
                pq.pop();
            }
            pq.push(a[i].p);
            ans+=pq.top();
            pq.pop();
        }else{
            pq.push(a[i].p);
        }
    }
    for (register int t=1; pq.size() && t<a[N-1].d; t++){
        ans+=pq.top();
        pq.pop();
    }
    printf("%d\n", ans);
}

bool myComp(const Node & x, const Node & y){
    return x.d>y.d || x.d==y.d && x.p>y.p;
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