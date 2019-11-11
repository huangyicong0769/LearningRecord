#include <iostream>
#include <cstdio>
#include <algorithm>
#define SIZE 20006
#define reg register
#define il inline
#define ll long long
#define f(a, b, c) for (reg int a=b; a<=c; a++)
using namespace std;

struct Line{
    ll x, y1, y2, v;
}a[SIZE*2];

struct STNode{
    ll l, r, dat, add;
}c[SIZE*8];

class SegmentTree{
    private:
        void build(int, int, int);
        il void spread(const int &); 
    public:
        SegmentTree(){}
        void rebuild(const int &, const int &, const int &);
        void modify(int, const int &, const int &, const ll &);
        ll ask();
}st;

ll N, W, H, M, raw[SIZE*2];

il void init();
bool myComp(const Line &, const Line &);

int main(){
    // freopen("input.txt", "r", stdin);
    while(~scanf("%lld%lld%lld", &N, &W, &H)){
        f (i, 1, N){
            scanf("%lld%lld%lld ", &a[i].x, &a[i].y1, &a[i].v);
            a[i+N].x=a[i].x+W;
            raw[i]=a[i+N].y1=a[i].y1;
            raw[i+N]=a[i].y2=a[i+N].y2=a[i].y1+H-1;
            a[i+N].v=-a[i].v;
        }
        init();
        ll ans=0;
        f (i, 1, N){
            st.modify(1, a[i].y1, a[i].y2, a[i].v);
                ans=max(ans, st.ask());
        }
        printf("%lld\n", ans);
    }   
}

il void init(){
    N<<=1;
    sort(a+1, a+1+N, myComp);
    sort(raw+1, raw+1+N);
    M=unique(raw+1, raw+1+N)-(raw+1);
    f (i, 1, N) {
        a[i].y1=lower_bound(raw+1, raw+M+1, a[i].y1)-(raw+1);
        a[i].y2=lower_bound(raw+1, raw+M+1, a[i].y2)-(raw+1);
    }
    st.rebuild(1, 1, M);
}

bool myComp(const Line & a, const Line & b){
    return a.x<b.x || a.x==b.x && a.v<b.v;
}

void SegmentTree::build(int p, int l, int r){
    c[p].l=l; c[p].r=r;
    c[p].dat=c[p].add=0;
    if (l==r) return;
    int mid=(l+r)>>1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
}

void SegmentTree::spread(const int & p){
    c[p<<1].dat+=c[p].add;
    c[p<<1|1].dat+=c[p].add;
    c[p<<1].add+=c[p].add;
    c[p<<1|1].add+=c[p].add;
    c[p].add=0;
}

void SegmentTree::rebuild(const int & a, const int & b, const int & c){
    build(a, b, c);
}

void SegmentTree::modify(int p, const int & x, const int & y, const ll & k){
    if (x<=c[p].l && c[p].r<=y) {
        c[p].add+=k;
        c[p].dat+=k;
        return;
    }
    if (c[p].add) spread(p);
    int mid=(c[p].l+c[p].r)>>1;
    if (x<=mid) modify(p<<1, x, y, k);
    if (mid<y) modify(p<<1|1, x, y, k);
    c[p].dat=max(c[p<<1].dat, c[p<<1|1].dat);
}

ll SegmentTree::ask(){
    return c[1].dat;
}