#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

int x[10010], y[10010]; 

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++) scanf("%d%d", &x[i], &y[i]);
    sort(x, x+N);
    sort(y, y+N);
    ll ans=0;
    for (int i=0; i<N; i++) x[i]-=i;
    sort(x, x+N);
    for (int i=0; i<N/2; i++) ans+=x[N-i-1]-x[i]+y[N-i-1]-y[i];
    printf("%ld\n", ans);
}