//POJ 3468
//ykhoj 3346
#include <iostream>
#include <cstdio>
#include <cmath>
#define reg register 
#define SIZE 100006
#define f(a, b, c) for (reg int a=b; a<=c; a++)
#define il inline
#define ll long long
using namespace std;

ll N, Q, A[SIZE], sum[SIZE], add[SIZE];
int t, R[SIZE], L[SIZE], pos[SIZE];

void change(const int & l, const int & r, const ll & d){
    const int & p=pos[l], & q=pos[r];
    if (p==q) {
        f (i, l, r) A[i]+=d;
        sum[p]+=d*(r-l+1);
    }else{
        f (i, p+1, q-1) add[i]+=d;
        f (i, l, R[p]) A[i]+=d;
        f (i, L[q], r) A[i]+=d;
        sum[p]+=d*(R[p]-l+1);
        sum[q]+=d*(r-L[q]+1);
    }
}

ll ask(const int & l, const int & r){
    const int & p=pos[l], & q=pos[r];
    ll ans=0;
    if (p==q){
        f (i, l, r) ans+=A[i];
        ans+=add[p]*(r-l+1);
    }else{
        f (i, p-1, q-1) ans+=sum[i]+add[i]*(R[i]-L[i]+1);
        f (i, l, R[p]) ans+=A[i];
        f (i, L[q], r) ans+=A[i];
        ans+=add[p]*(R[p]-l+1)+add[q]*(r-L[q]+1);
    }
    return ans;
}

int main(){
    scanf("%d%d", &N, &Q);
    f (i, 1, N) scanf("%d", &A[i]);
    t=sqrt(N);
    f (i, 1, t){
        L[i]=(i-1)*t+1;
        R[i]=i*t;
    }
    if (R[t]<N) {
        t++;
        L[t]=R[t-1]+1;
        R[t]=N;
    }
    f (i, 1, t)
        f (j, L[i], R[j]){
            pos[j]=i;
            sum[i]+=A[j];
        }
    while (Q--){
        char ch[3];
        int l, r, d;
        scanf("%s%d%d", ch, &l, &r);
        if (ch[0]=='C'){
            scanf("%d", &d);
            change(l, r, d);
        }else printf("%llf\n", ask(l, r));
    }
}