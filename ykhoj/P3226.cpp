#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll s[1000100];

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N;
    scanf("%d", &N);
    ll sum=0;
    for (int i=0; i<N; i++) {
        scanf("%lld", &s[i]);
        sum+=s[i];
    }
    sum/=N;
    for (int i=0; i<N; i++) s[i]+=s[i-1]-sum;
    sort(s, s+N);
    ll ans=0;
    for (int i=0; i<N/2; i++) ans+=s[N-i-1]-s[i];
    printf("%lld\n", ans);
}