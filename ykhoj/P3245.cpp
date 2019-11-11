#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N=read();
    priority_queue<int> pq;
    for (int i=0; i<N; i++) pq.push(-1*read());
    int ans=0;
    for (int i=1; i<N; i++) {
        int now1=-1*pq.top(); pq.pop();
        int now2=-1*pq.top(); pq.pop();
        ans+=now1+now2;
        pq.push(-1*now1+-1*now2);
    }
    printf("%d\n", ans);
}

inline int read(){
    int x=0, f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}