#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, less<int> > h1;
priority_queue<int, vector<int>, greater<int> > h2;

int A[30010], U[30010];
inline int read();

int main(){
    const int M=read(), N=read();
    for (register int i=0; i<M; i++) A[i]=read();
    for (register int i=0; i<N; i++) U[read()]++;
    for (register int tp=0, i=0; tp<=M;){
        if (U[tp]){
            i++;
            printf("%d\n", h1.top());
            U[tp]--;
        }else {
            h1.push(A[tp]);
            tp++;
        }
        while (h1.size() && h2.size() && h1.top()>h2.top()){
            int t1=h1.top(),
                t2=h2.top();
            h1.pop(); h2.pop();
            h1.push(t2); h2.push(t1);
        }
        while (h1.size()>i+1) {
            h2.push(h1.top());
            h1.pop();
        }
        while (h2.size() && h1.size()<=i) {
            h1.push(h2.top());
            h2.pop();
        }
    }
    // printf("=====\n");
    // while (h1.size()){
    //     printf("%d ", h1.top());
    //     h1.pop();
    // }printf("\n");
    // while (h2.size()){
    //     printf("%d ", h2.top());
    //     h2.pop();
    // }printf("\n");
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