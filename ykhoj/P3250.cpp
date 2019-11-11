#include <iostream>
#include <cstdio>
#include <queue>
#include <deque>
using namespace std;

struct Node{
    int pos, v;
    Node(const int& pos, const int& v){
        this->pos=pos;
        this->v=v;
    }
};

int ans1[1001000], ans2[1001000];
deque<Node> qmax, qmin;

inline int read();

int main(){
    //freopen("input.txt", "r", stdin);
    int N=read(), K=read();
    for (int i=0; i<N; i++){
        int a=read();
        while (!qmin.empty() && qmin.front().pos+K<=i) qmin.pop_front();
        while (!qmin.empty() && qmin.back().v>=a) qmin.pop_back();
        qmin.push_back(Node(i, a));
        ans1[i]=qmin.front().v;
        while (!qmax.empty() && qmax.front().pos+K<=i) qmax.pop_front();
        while (!qmax.empty() && qmax.back().v<=a) qmax.pop_back();
        qmax.push_back(Node(i, a));
        ans2[i]=qmax.front().v;
    }
    for (int i=K-1; i<N; i++) printf("%d ", ans1[i]); printf("\n");
    for (int i=K-1; i<N; i++) printf("%d ", ans2[i]); printf("\n");
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