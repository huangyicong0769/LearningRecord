//Ch 4601
//ykhoj 3356
//Tyvj 1728
//BZOJ 3224
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#define SIZE 100010
#define reg register
#define INF 0x7FFFFFFF
#define il inline
#define f(a, b, c) for (reg int a = b; a <= c; a++)
using namespace std;

struct TreapNode{
    int l, r, cnt, size, dat, val;
}a[SIZE];

class Treap{
    int tot;
    il void Update(const int &p){ 
        a[p].size = a[p].cnt + a[a[p].l].size + a[a[p].r].size; }
    
    il void Zig(int &p){
        // printf("r%d\n", p);
        reg int q = a[p].l;
        a[p].l = a[q].r; a[q].r = p; p = q;
        Update(a[p].r), Update(p);
    }

    il void Zag(int &p){
        // printf("l%d\n", p);
        reg int q = a[p].r; 
        a[p].r = a[q].l; a[q].l = p; p = q;
        Update(a[p].l), Update(p);
    }

    il int New(int val){
        a[++tot].dat=rand();
        a[tot].val=val;
        a[tot].cnt=a[tot].size=1;
        return tot;
    }

    il void Build(){
        tot=0;
        New(-INF), New(INF);
        root = 1;
        a[1].r = 2;
        Update(root);
    }

  public:
    int root;
    Treap() { Build(); }

    void Insert(int &p, int val){
        // printf("->%d", p);
        if (p == 0){
            p = New(val);
            // printf("->%d\n", p);
            return;
        }
        if (a[p].val == val){
            a[p].cnt++, Update(p);
            return;
        }
        if (a[p].val > val){
            Insert(a[p].l, val);
            if (a[a[p].l].dat > a[p].dat) Zig(p);
        }
        else{
            Insert(a[p].r, val);
            // printf("p:%d r:%d rd:%d d:%d\n", p, a[p].r, a[a[p].r].dat, a[p].dat);
            if (a[a[p].r].dat > a[p].dat) Zag(p);
        }
        Update(p);
    }

    il int GetPre(int val){
        int p = root, ans = 1;
        while (p) {
            if (a[p].val == val){
                if (a[p].l>0){
                    p = a[p].l;
                    while (a[p].r>0) p = a[p].r;
                    ans = p;
                }
                break;
            }
            if (a[p].val < val && a[p].val > a[ans].val) ans = p;
            p = a[p].val < val ? a[p].r : a[p].l;
        }
        return a[ans].val;
    }

    il int GetNext(int val) {
        int p = root, ans = 2;
        while (p) {
            if (a[p].val == val) {
                if (a[p].r>0) {
                    p = a[p].r;
                    while (a[p].l>0) p = a[p].l;
                    ans = p;
                }
                break;
            }
            if (a[p].val > val && a[p].val < a[ans].val) ans = p;
            p = a[p].val < val ? a[p].r : a[p].l;
        }
        return a[ans].val;
    }

    int GetRankByVal(int p, int val) {
        if (p == 0)  return 0;
        if (a[p].val == val) return a[a[p].l].size + 1;
        if (val < a[p].val) return GetRankByVal(a[p].l, val);
        return GetRankByVal(a[p].r, val) + a[a[p].l].size + a[p].cnt;
    }

    int GetValByRank(int p, int rank){
        if (p == 0)  return INF;
        if (a[a[p].l].size >= rank) return GetValByRank(a[p].l, rank);
        if (a[a[p].l].size + a[p].cnt >= rank) return a[p].val;
        return GetValByRank(a[p].r, rank - a[a[p].l].size - a[p].cnt);       
    }

    void Remove(int &p, int val) {
        if (p == 0) return;
        if (a[p].val == val) {
            if (a[p].cnt > 1) {
                a[p].cnt--, Update(p);
                return;
            }
            if (a[p].l || a[p].r) {
                if (a[p].r == 0 || a[a[p].l].dat > a[a[p].r].dat) 
                    Zig(p), Remove(a[p].r, val);
                else Zag(p), Remove(a[p].l, val);
                Update(p);
            }
            else p = 0;
            return;
        }
        val < a[p].val ? Remove(a[p].l, val) : Remove(a[p].r, val);
        Update(p);
    }

    void debug(){
        printf("root:%d\n", root);
        f (i, 0, tot) printf("id:%d l:%d r:%d cnt:%d size:%d dat:%d val:%d\n",
            i, a[i].l, a[i].r, a[i].cnt, a[i].size, a[i].dat, a[i].val);
        printf("\n");
    }
};

int main(){
    // freopen("output.txt", "w", stdout);
    Treap tr;
    // tr.debug();
    int N; scanf("%d", &N);
    f(i, 1, N) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1) tr.Insert(tr.root, x);
        if (opt == 2) tr.Remove(tr.root, x);
        if (opt == 3) printf("%d\n", tr.GetRankByVal(tr.root, x) - 1);
        if (opt == 4) printf("%d\n", tr.GetValByRank(tr.root, x + 1));
        if (opt == 5) printf("%d\n", tr.GetPre(x));
        if (opt == 6) printf("%d\n", tr.GetNext(x));
        // tr.debug();
    }
}