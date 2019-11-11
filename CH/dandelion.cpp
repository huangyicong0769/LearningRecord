//ykhoj 3352
//Ch 4401
//BZOJ 2724
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#define SIZE 40006
#define T 806
#define reg register
#define il inline
#define ll long long
#define f(i, s, t) for (reg int i=s; i<=t; i++)
using namespace std;

int N, M, tot, a[SIZE], b[SIZE], R[SIZE], L[SIZE], f[T][T], pos[SIZE];
vector<int> v[SIZE];

il void work(int x, const int &l, const int &r, int & ans, int & cnt){
    int w=upper_bound(v[x].begin(), v[x].end(), r)-lower_bound(v[x].begin(), v[x].end(), l);
    if (w>cnt || w==cnt && x<ans){
        cnt=w;
        ans=x;
    }
}

il int ask(const int & l, const int & r){
    const int &p=pos[l], &q=pos[r];
    int ans=0, cnt=0;
    if (p==q)
        f (i, l, r) work(a[i], l, r, ans, cnt);
    else{
        if (p+1<=q-1) if (f[p+1][q-1]) work(f[p+1][q-1], l, r, ans, cnt);
        f (i, l, R[p]) work(a[i], l, r, ans, cnt);
        f (i, L[q], r) work(a[i], l, r, ans, cnt);
    }
    return b[ans];
}

il void init(){
    memcpy(b, a, sizeof(a));
    sort (b+1, b+1+N);
    tot=unique(b+1, b+1+N)-(b+1);
    f (i, 1, N){
        a[i]= lower_bound(b+1, b+1+tot, a[i])-b;
        v[a[i]].push_back(i);
    }
    // f (i, 1, N) printf("%d ", a[i]); puts("");
    int t=sqrt(N*log2(N)),
        len=t?N/t:N;
    f (i, 1, t){
        L[i]=(i-1)*len+1;
        R[i]=i*len;
    }
    // printf("%d\n", len);
    // printf("%d\n", t);
    if (R[t]<N){
        t++;
        L[t]=R[t-1]+1;
        R[t]=N;
    }
    // printf("%d\n", t);
    f (i, 1, t) f (j, L[i], R[i]) pos[j]=i;
    f (i, 1, t){
        int cnt=0, ans=0, c[SIZE]={0};
        f (j, L[i], N){
            if (++c[a[j]]>cnt || c[a[j]]==cnt && a[j]<ans){
                ans=a[j];
                cnt=c[a[j]];
            }
            f[i][pos[j]]=ans;
        }
    }
    // f (i, 1, t) {f (j, i, t) printf("%d ", f[i][j]); puts("");}
}

int main(){
    scanf("%d%d", &N, &M);
    f (i, 1, N) scanf("%d", &a[i]);
    init();
    int x=0;
    f (i, 1, M){
        int l, r;
        scanf("%d%d", &l, &r);
        l=(l+x-1)%N+1; 
        r=(r+x-1)%N+1;
        if (l>r) swap(l, r);
        x=ask(l, r);
        printf("%d\n", x);
    }
}