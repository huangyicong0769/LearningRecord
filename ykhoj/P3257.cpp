#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

typedef long long ll;

struct Node{
    int y;
    Node(const int &);
    bool operator<(const Node &)const;
};

priority_queue<Node> pq;

int a[100100], l[100100], r[100100];
bool leaf[100100];

inline int read();
inline void remove(const int );

int main(){
    int N=read(), M=read();
    if (N==0) puts("0");
    int last=-1, cnt=0;
    for (register int i=1; i<=N; i++){
        int t=read();
        if (t==0) continue;
        if ((ll) last*t>=0) a[cnt]+=t;
        else a[++cnt]=t;
        last=t;
    }
    N=cnt; cnt=0; 
    int ans=0;
    for  (register int i=1; i<=N; i++){
        if (a[i]>0) ++cnt, ans+=a[i];
        l[i]=i-1; r[i]=i+1;
        pq.push(Node(i));
    }
    while (cnt>M){
        while (leaf[pq.top().y]) pq.pop();
        int t=pq.top().y; pq.pop();
        if (a[t]>0 || l[t]>0 && r[t]<=N){
            cnt--;
            ans-=abs(a[t]);
            a[t]+=a[l[t]]+a[r[t]];
            remove(l[t]); 
            remove(r[t]);
            pq.push(Node(t));
        }else remove(t);
    }
    printf("%d\n", ans);
}

Node::Node(const int & y){
    this->y=y;
}

bool Node::operator<(const Node & x)const{
    return abs(a[(this->y)])>abs(a[x.y]);
}

inline int read(){
    int x=0, f=1; register char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x*f;
}

inline void remove(const int pos){
    r[l[pos]]=r[pos];
    l[r[pos]]=l[pos];
    leaf[pos]=1;
}