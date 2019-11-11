#include <iostream>
#include <cstdio>
#define SIZE 500006
#define reg register
#define f(a, b, c) for (reg int a=b; a<=c; a++)
#define il inline
using namespace std;

struct stNode{
    int l, r, dat, sum, lmax, rmax;
};

stNode v[SIZE*4];
int A[SIZE];

class SegmentTree{
    private:
        il void update(const int &);
        void build(int, int, int);
    public:
        SegmentTree(int, int, int);
        void modify(int, const int &, const int &);
        stNode ask(int, const int &, const int &);
};

il int read();

int main(){
    int N, M;
    scanf("%d", &N);
    f (i, 1, N) scanf("%d", &A[i]);
    SegmentTree segT(1, 1, N);
    scanf("%d", &M);
    f (i, 1, M){
        int st, x, y;
        scanf("%d%d%d", &st, &x, &y);
        if (st==1) {
            if (x>y) swap(x, y);
            cout<<segT.ask(1, x, y).dat<<endl;
        }
        else segT.modify(1, x, y);
    }
}

il void SegmentTree::update(const int & p){
    v[p].sum=v[p*2].sum+v[p*2+1].sum;
    v[p].lmax=max(v[p*2].lmax, v[p*2].sum+v[p*2+1].lmax);
    v[p].rmax=max(v[p*2+1].rmax, v[p*2+1].sum+v[p*2].rmax);
    v[p].dat=max(v[p*2].rmax+v[p*2+1].lmax, max(v[p*2].dat, v[p*2+1].dat));
}

SegmentTree::SegmentTree(int p, int l, int r){
    build(p, l, r);
}

void SegmentTree::build(int p, int l, int r){
    v[p].l=l; v[p].r=r;
    if (l==r) {
        v[p].sum=v[p].dat=v[p].lmax=v[p].rmax=A[l];
        return;
    }
    int mid=(l+r)/2;
    build (p*2, l, mid);
    build (p*2+1, mid+1, r);
    update(p);
}

void SegmentTree::modify(int p, const int & x, const int & y){
    if (v[p].l==v[p].r) {
        v[p].dat=v[p].sum=v[p].lmax=v[p].rmax=y;
        return;
    }
    int mid=(v[p].l+v[p].r)/2;
    if (x<=mid) modify (p*2, x, y);
    else modify (p*2+1, x, y);
    update(p);
}

stNode SegmentTree::ask(int p, const int & x, const int & y){
    if (x<=v[p].l && v[p].r<=y) return v[p];
    int mid=(v[p].l+v[p].r)/2;
    stNode ans, a, b;
    a.sum=b.sum=a.lmax=a.dat=a.rmax=b.lmax=b.dat=b.rmax=-(1<<30);
    ans.sum=0;
    if (x<=mid) {
        a=ask(p*2, x, y);
        ans.sum+=a.sum;
    }
    if (mid<y) {
        b=ask(p*2+1, x, y);
        ans.sum+=b.sum;
    }
    ans.dat=max(max(a.dat, b.dat), a.rmax+b.lmax);
    ans.lmax=max(a.lmax, a.sum+b.lmax);
    ans.rmax=max(b.rmax, a.rmax+b.sum);
    if (mid<x) ans.lmax=max(ans.lmax, b.lmax);
    if (y<=mid) ans.rmax=max(ans.rmax, a.rmax);
    return ans;
}

il int read(){
    reg int x=0, f=1; reg char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
    return x*f;
}