#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int v[200010], p[200010], sm[200010], sn[200010];

inline int read();
bool myComp(const int&, const int&);

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N=read();
    for (int i=1; i<=N; i++) {
        p[i]=i;
        v[i]=read();
    }
    sort(p+1, p+N+1, myComp);
    v[0]=-1;
    int m=0;
    for (int i=1; i<=N; i++){
        if (v[p[i]]!=v[p[i-1]]) m++, sm[m]=sn[m]=p[i];
        sm[m]=max(sm[m], p[i]); 
        sn[m]=min(sn[m], p[i]);
    }
    bool tend=1; int last=200010, ans=0;
    for (int i=1; i<=m; i++){
        if (tend && sn[i]<last) {
            ans++;
            tend=0;
            last=sn[i];
        }else if (!tend && sm[i]>last) {
            tend=1;
            last=sm[i];
        }else if (!tend && sm[i]<last) last=sn[i];
        else if (tend && sn[i]>last) last=sm[i];
    }
    printf("%d\n", ans);
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

bool myComp(const int& a, const int& b){
    return v[a]<v[b] || v[a]==v[b] && a<b;
}