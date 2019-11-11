#include <iostream>
#include <cstdio>
#include <queue>
#include <deque>
using namespace std;

typedef long long ll;

ll s[300100];
deque<int> dq;

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N=read(), M=read();
    for (int i=0; i<N; i++) s[i]=s[i-1]+read();
    ll ans=0;
    for (int i=0; i<N; i++) {
        while (dq.size()!=0 && dq.front()<i-M) dq.pop_front();
        if (dq.size()!=0) ans=max(ans, s[i]-s[dq.front()]);
        while (dq.size()!=0 && s[dq.back()]>=s[i]) dq.pop_back();
        dq.push_back(i);
    }
    printf("%lld\n", ans);
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