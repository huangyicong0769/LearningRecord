#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

typedef long long ll;

int h[100100];
struct Tuple{
    int height, width;
    Tuple(const int&, const int&);
};
stack<Tuple> s;

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    while(1){   
        int N=read();
        if (N==0) break;
        for(int i=0; i<N; i++) h[i]=read(); 
        h[N]=0;
        ll ans=0;
        for (int i=0; i<=N; i++){
            if (s.size()==0 || s.top().height<h[i]) s.push(Tuple(h[i], 1));
            else{
                int w=0;
                while (s.size()>0 && s.top().height>=h[i]){
                    w+=s.top().width;
                    ans=max(ans, 1LL*w*s.top().height);
                    s.pop();
                }
                s.push(Tuple(h[i], w+1));
            }
        }
        printf("%lld\n", ans);
    }
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

Tuple::Tuple(const int& a, const int& b){
    this->height=a;
    this->width=b;
}