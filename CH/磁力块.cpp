#pragma GCC optimize(3,"Ofast","inline")
//CH #46A
//ykhoj 3353
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#define reg register
#define il inline
#define ll long long
#define SIZEN 250006
#define SIZET 600
#define f(a, b, c) for (reg int a=b; a<=c; a++)
using namespace std;

struct Stone{
    ll m, p, r, d;
}a[SIZEN];

ll xO, yO, pL, rL, N, T, R[SIZET], L[SIZET], M[SIZET];
bool b[SIZEN];

bool comp1(const Stone &x, const Stone &y) {return x.m<y.m;}
bool comp2(const Stone &x, const Stone &y) {return x.d<y.d;}

il void init(){
    sort(a+1, a+1+N, comp1);
    T=sqrt(N);
    f (i, 1, T) L[i]=(i-1)*T+1, R[i]=i*T;
    if (R[T]<N) L[++T]=R[T-1]+1, R[T]=N;
    f (i, 1, T) {
        M[i]=a[R[i]].m;
        sort(a+L[i], a+R[i]+1, comp2);
    }
    // f (i, 1, T) printf("%lld %lld\n", L[i], R[i]);
    // f (i, 0, N) printf("%lld %lld %lld %lld\n",a[i].m, a[i].p, a[i].r, a[i].d);
}

int main(){
    // freopen("input.txt", "r", stdin);
    scanf("%lld%lld%lld%lld%lld", &xO, &yO, &a[0].p, &a[0].r, &N);
    a[0].r*=a[0].r; a[0].d=0;
    f (i, 1, N) {
        ll x, y;
        scanf("%lld%lld%lld%lld%lld", &x, &y, &a[i].m, &a[i].p, &a[i].r);
        a[i].r*=a[i].r;
        a[i].d=(x-xO)*(x-xO)+(y-yO)*(y-yO);
    }
    init();
    int ans=0;
    queue<int> q;
    q.push(0);
    b[0]=1;
    while (q.size()) {
        int k=0, x=q.front(); q.pop();
        f (i, 1, T) if (a[x].p>=M[i]) k=i; else break;
        // printf("!%d %d\n", x, k);
        f (i, 1, k)
            while (L[i]<=R[i] && a[L[i]].d<=a[x].r){
                // printf("%d\n", L[i]);
                L[i]++;
                if (b[L[i]-1]) continue;
                b[L[i]-1]=1;
                ans++;
                q.push(L[i]-1);
            }
        if (T!=k++) f (j, L[k], R[k]) if (!b[j] && a[j].d<=a[x].r && a[x].p>=a[j].m){
            ans++;
            q.push(j);
            b[j]=1;
        }
    }
    // int cnt=0;
    // f (i, 1, N) if (b[i]) cnt++;
    // printf("%d\n", cnt);
    printf("%d\n", ans);
}