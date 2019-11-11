#include <cstdio>

typedef long long ll;

inline int readN();
inline void swap(int&, int&);

int main(){
    int S=readN(), T=readN();
    if (S>T) swap(S, T);
    ll ans=0;
    for (int i=1; i<=T; i++){
        int t1=S/i,
            t2=T/i;
        if (S%i==0) t1--;
        ans+=t2-t1;
    }
    printf("%lld\n", ans);
}

inline int readN(){
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

inline void swap(int& a, int& b){
    int t=a;
    a=b;
    b=t;
}