#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct Node{
    int i, j;
    bool last;
    Node();
    Node(int , int , bool);
    bool operator<(const Node&)const;
};

int a[2][2010], b[2010], m;

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    for (int T=read(); T; T--){
        int M=read(), N=read();
        for (m=0; m<M; m++){
            for (int n=0; n<N; n++) a[m&1][n]=read();
            sort(a[m&1], a[m&1]+N);
            if (m==0) {
                for (int n=0; n<N; n++) b[n]=a[m&1][n];
                continue;
            }
            priority_queue<Node> pq;
            pq.push(Node());
            for (int k=0; k<N; k++){
                Node now=pq.top(); pq.pop();
                //printf("%d %d %d\n", now.i, now.j, now.last);
                b[k]=a[m&1][now.i]+a[1^(m&1)][now.j];
                pq.push(Node(now.i, now.j+1, 1));
                if (!now.last) pq.push(Node(now.i+1, now.j, 0));
            } 
            for (int n=0; n<N; n++) a[m&1][n]=b[n];
        }
        for (int i=0; i<N; i++) printf("%d ", b[i]); printf("\n");
    }
    return 0;
}

Node::Node(){
    i=j=last=0;
}

Node::Node(int i, int j, bool last){
    this->i=i;
    this->j=j;
    this->last=last;
}

bool Node::operator<(const Node& node)const{
    return a[m&1][this->i]+a[1^(m&1)][this->j]>a[m&1][node.i]+a[1^(m&1)][node.j];
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