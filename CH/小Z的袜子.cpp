//CH 4402
//ykhoj 3354
//BZOJ 2038
//luogu 1494
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define SIZE 50006
#define reg register
#define ll long long
#define il inline
#define f(a, b, c) for (reg int a=b; a<=c; a++)
using namespace std;

int N, M, a[SIZE], L[SIZE], R[SIZE], c[SIZE];
ll ans, fa[SIZE][2];

struct Ques{ int l, r, id; }b[SIZE];

bool comp1(const Ques &a, const Ques &b) {return a.l<b.l;}
bool comp2(const Ques &a, const Ques &b) {return a.r<b.r;}

ll gcd(ll x, ll y){return y?gcd(y, x%y):x;}

il void work(const int &x, const int &y){
    ans-=(ll)c[a[x]]*(c[a[x]]-1);
    c[a[x]]+=y;
    ans+=(ll)c[a[x]]*(c[a[x]]-1);
}

int main(){
    scanf("%d%d", &N, &M);
    f (i, 1, N) scanf("%d", &a[i]);
    f (i, 1, M) scanf("%d%d", &b[i].l, &b[i].r), b[i].id=i;
    sort(b+1, b+M+1, comp1);
    int t=sqrt(M);
    f (i, 1, t){
        L[i]=(i-1)*t+1;
        R[i]=i*t;
        sort(b+L[i], b+R[i]+1, comp2);
    }
    if (R[t]<M) {
        L[++t]=R[t-1]+1;
        R[t]=M;
        sort(b+L[t], b+R[t]+1, comp2);
    }
    // f (i, 1, t) printf("%d %d\n", L[i], R[i]);
    // f (i, 1, M) printf("%d %d %d\n", b[i].l, b[i].r, b[i].id);
    f (i, 1, t){
        ans=0;
        memset(c, 0, sizeof(c));
        int l=b[L[i]].l, r=b[L[i]].r;
        f (j, l, r) work(j, 1);
        fa[b[L[i]].id][0]=ans;
        fa[b[L[i]].id][1]=(ll)(r-l)*(r-l+1);
        // printf("?%lld/%lld\n", fa[b[L[i]].id][0], fa[b[L[i]].id][1]);
        ll g=gcd(fa[b[L[i]].id][0], fa[b[L[i]].id][1]);
        if (!g) fa[b[L[i]].id][1]=1;
        else fa[b[L[i]].id][0]/=g, fa[b[L[i]].id][1]/=g;
        // printf("!%lld/%lld, %lld\n", fa[b[L[i]].id][0], fa[b[L[i]].id][1], g);
        f (j, L[i]+1, R[i]){
            while (r>b[j].r) work(r--, -1);
            while (r<b[j].r) work(++r, 1);
            while (l<b[j].l) work(l++, -1);
            while (l>b[j].l) work(--l, 1);
            if (l==r) fa[b[j].id][0]=0, fa[b[j].id][1]=1;
            else{
                fa[b[j].id][0]=ans;
                fa[b[j].id][1]=(ll)(r-l)*(r-l+1);
                ll g=gcd(fa[b[j].id][0], fa[b[j].id][1]);
                if (!g) fa[b[j].id][1]=1;
                else fa[b[j].id][0]/=g, fa[b[j].id][1]/=g;
            }
        }
    }
    f (i, 1, M) printf("%lld/%lld\n", fa[i][0], fa[i][1]);
}