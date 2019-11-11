#include <iostream>
#include <queue>
#include <cstdio>
#define INT_MAX (1<<31)-1
using namespace std;

struct Node{
    int T, M, P, next, pos;
} data[10100];

queue<int> waitQ;
int endT, countWaitQ, nextT, curT, maxMem, root;

inline int read();
inline void free();
inline bool process(const int&, const int&); //success -> false

int main(){
    maxMem=read();
    data[1].T=read(); data[1].M=read(); data[1].P=read(); curT=data[1].T;
    for (int i=1; data[i].T!=0 || data[i].M!=0 || data[i].P!=0; data[++i].T=read(), data[i].M=read(), data[i].P=read(), curT=data[i].T){
        while (curT>=nextT) free();
        if (process(i, curT)) countWaitQ++, waitQ.push(i);
        else nextT=min(nextT, data[i].T+data[i].P);
    }
    while (waitQ.size()) free();
    endT=nextT;
    for (int i=root; i; i=data[i].next) endT=max(endT, data[i].T+data[i].P);
    printf("%d\n%d\n", endT, countWaitQ);
    return 0;
}

inline int read(){
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

inline void free(){
    int tT=INT_MAX;
    for (int i=root, pre=root; i; i=data[i].next)
        if (data[i].T+data[i].P==nextT){
            if (i==root) root=data[i].next;
            else data[pre].next=data[i].next;
        }else tT=min(tT, data[i].T+data[i].P), pre=i;
    while (waitQ.size() && !process(waitQ.front(), nextT)) tT=min(tT, data[waitQ.front()].T+data[waitQ.front()].P), waitQ.pop();
    nextT=tT; 
}

inline bool process(const int& id, const int& t){
    if (!root || data[root].pos>=data[id].M){
        data[id].next=root;
        root=id;
        data[id].pos=0;
        data[id].T=t;
        return false;
    }
    for (int i=root; i; i=data[i].next){
        if ((data[i].next?data[data[i].next].pos:maxMem)-(data[i].pos+data[i].M)>=data[id].M){
            data[id].next=data[i].next;
            data[i].next=id;
            data[id].pos=data[i].pos+data[i].M;
            data[id].T=t;
            return false;
        }
    }
    return true;
}