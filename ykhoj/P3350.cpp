#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
#define reg register
#define il inline
#define f(a, b, c) for (reg int a=b; a<=c; a++)
#define SIZE 110
using namespace std;

struct Line{
    double x, y1, y2;
    int v;
}a[SIZE*2];

struct STNode{
    int l, r, cnt;
    double len;
};

class SegmentTree{
    private:
        STNode c[SIZE*8];
        void build(int, int, int);
    public:
        SegmentTree(const int &, const int &, const int &);
        void modify(int, const int &, const int &, const double &);
        double ask();
};

int N, M, cnt;
double raw[SIZE*2];
map<double, int> val;

il void init();
bool myComp(const Line &, const Line &);

int main(){
    for (scanf("%d", &N); N; scanf("%d", &N)){
        f (i, 1, N){
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a[i].x=x1; a[i+N].x=x2;
            a[i].y1=a[i+N].y1=y1;
            a[i].y2=a[i+N].y2=y2;
            a[i].v=1; a[i+N].v=-1;
            raw[i]=y1; raw[i+N]=y2;
        }
        init();
        SegmentTree st(1, 1, M-1);
        double ans=0;
        f (i, 1, N-1){
            // cout<<i<<endl;
            int y1=val[a[i].y1], y2=val[a[i].y2]-1;
            st.modify(1, y1, y2, a[i].v);
            ans+=st.ask()*(a[i+1].x-a[i].x);
            // cout<<st.ask()<<' '<<(a[i+1].x-a[i].x)<<endl;
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++cnt, ans);
    }
}

il void init(){
    N*=2;
    sort(raw+1, raw+N+1);
    M=unique(raw+1, raw+N+1)-(raw+1);
    f (i, 1, M) val[raw[i]]=i;
    sort(a+1, a+N+1, myComp); 
    // f (i, 1, M) cout<<raw[i]<<' '; cout<<endl;
    // f (i, 1, M) cout<<val[raw[i]]<<' '; cout<<endl;
}

bool myComp(const Line & a, const Line & b){
    return a.x<b.x;
}

SegmentTree::SegmentTree(const int & a, const int & b, const int & c){
    build(a, b, c);
}

void SegmentTree::build(int p, int l, int r){
    // cout<<p<<' '<<l<<' '<<r<<endl;
    c[p].cnt=c[p].len=0;
    c[p].l=l; c[p].r=r;
    if (l==r) return;
    int mid=(l+r)/2;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
}

void SegmentTree::modify(int p, const int & x, const int & y, const double & k){
    // cout<<p<<' '<<x<<' '<<y<<' '<<k<<endl;
    if (x<=c[p].l && c[p].r<=y)  c[p].len=(c[p].cnt+=k)?(raw[c[p].r+1]-raw[c[p].l]):0;
    if (c[p].l==c[p].r) return;
    int mid=(c[p].l+c[p].r)>>1;
    if (x<=mid) modify(p<<1, x, y, k);
    if (mid<y) modify(p<<1|1, x, y, k);
    c[p].len=c[p].cnt?(raw[c[p].r+1]-raw[c[p].l]):(c[p<<1].len+c[p<<1|1].len);
    // cout<<p<<' '<<c[p].cnt<<' '<<raw[c[p].r+1]-raw[c[p].l]
    // <<' '<<c[p<<1].len+c[p<<1|1].len<<endl;
}

double SegmentTree::ask(){
    return c[1].len;
}