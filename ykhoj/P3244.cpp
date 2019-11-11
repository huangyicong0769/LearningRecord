#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

typedef long long ll;

const ll INF=(1<<31)-1;

struct Element{
    int pos, val;
    Element(const int&, const int&);
    bool operator<(const Element&)const;
};

ll d[100010], l[100010], nex[100010], pre[100010];

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N=read(), K=read();
    priority_queue<Element> pq;
    for (int i=0; i<N; i++){
        d[i]=read();
        if (i==0) continue; 
        l[i]=d[i]-d[i-1];
        nex[i]=i+1;
        pre[i]=i-1;
        pq.push(Element(i, l[i]));
    }
    nex[N-1]=0;
    ll ans=0;
    for (int i=0; i<K; i++){
        Element now=pq.top(); pq.pop();
        if (now.val!=l[now.pos]){
            --i;
            continue;
        }
        ans+=now.val;
        int pr=pre[now.pos], ne=nex[now.pos];
        nex[now.pos]=nex[ne]; pre[nex[ne]]=now.pos;
        pre[now.pos]=pre[pr]; nex[pre[pr]]=now.pos;
        if (pr==0 || ne==0) now.val=INF;
        else now.val=min(INF, l[pr]+l[ne]-now.val);
        l[now.pos]=now.val;
        l[pr]=l[ne]=INF;
        pq.push(now);
    }
    printf("%lld\n", ans);
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

Element::Element(const int &pos, const int &val){
    this->pos=pos;
    this->val=val;
}

bool Element::operator<(const Element& ele)const{
    return this->val>ele.val;
}