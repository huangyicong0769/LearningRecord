#include <iostream>
#include <cstdio>
#include <cmath>
#define il inline
#define reg register
#define ll long long
#define f(a, b, c) for (reg int a = b; a <= c; a++)
#define SIZE 500010
#define lowbit(x) x&-x
using namespace std;

int N, M;
ll A[SIZE], B[SIZE], vb[SIZE];

struct STNode{
    int l, r;
    ll dat;
} vs[SIZE * 4];

class BinaryIndexTree{
  public:
    ll ask(int);
    void modify(int, const ll &);
};

class SegmentTree{
  private:
    void build(int, int, int);
  public:
    SegmentTree(const int &, const int &, const int &);
    void modify(int, const int &, const ll &);
    ll ask(int, const int &, const int &);
};

ll gcd(ll, ll);

int main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    scanf("%d%d", &N, &M);
    f (i, 1, N) scanf("%lld", &A[i]);
    f (i, 1, N) B[i]=A[i]-A[i-1];
    SegmentTree st(1, 1, N);
    BinaryIndexTree bit;
    f(m, 1, M){
        char ch[2];
        int l, r;
        scanf("%s%d%d", ch, &l, &r);
        if (ch[0] == 'Q'){
            printf("%lld\n", gcd(A[l] + bit.ask(l), l < r ? st.ask(1, l + 1, r) : 0));
        }else if (ch[0] == 'C'){
            ll d;
            scanf("%lld", &d);
            bit.modify(l, d);
            bit.modify(r + 1, -d);
            st.modify(1, l, d);
            if (r<N) st.modify(1, r + 1, -d);
        }
    }
}

ll BinaryIndexTree::ask(int x){
    ll ans=0;
    for (; x; x-=lowbit(x)) ans+=vb[x];
    return ans;
}

void BinaryIndexTree::modify(int x, const ll & y){
    for (; x<=N; x+=lowbit(x)) vb[x]+=y;
}

void SegmentTree::build(int p, int l, int r){
    vs[p].l=l; vs[p].r=r;
    if (vs[p].l==vs[p].r){
        vs[p].dat=B[l];
        return;
    }
    int mid=(l+r)/2;
    build (p<<1, l, mid);
    build (p<<1|1, mid+1, r);
    vs[p].dat=gcd(vs[p<<1].dat, vs[p<<1|1].dat);
}

SegmentTree::SegmentTree(const int & x, const int & y, const int & z){
    build (x, y, z);
}

void SegmentTree::modify(int p, const int & x, const ll & y){
    if (vs[p].l==vs[p].r){
        vs[p].dat+=y;
        return;
    }
    int mid=(vs[p].l+vs[p].r)/2;
    if (x<=mid) modify(p<<1, x, y); 
    else modify(p<<1|1, x, y);
    vs[p].dat=gcd(vs[p<<1].dat, vs[p<<1|1].dat);
}

ll SegmentTree::ask(int p, const int & x, const int & y){
    if (x<=vs[p].l && vs[p].r<=y) return abs(vs[p].dat);
    ll v=0;
    int mid=(vs[p].l+vs[p].r)/2;
    if (x<=mid) v=gcd(v, ask(p<<1, x, y));
    if (mid<y) v=gcd(v, ask(p<<1|1, x, y));
    return abs(v);
}

ll gcd(ll x, ll y){
    return y?gcd(y, x%y):x;
}