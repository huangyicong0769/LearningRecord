#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll a[10010];

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int T;
    scanf("%d", &T);
    for (int tt=1; tt<=T; tt++){
        ll N;
        int M;
        scanf("%lld%d", &N, &M);
        for (int i=0; i<M; i++) scanf("%lld", &a[i]);
        sort(a, a+M);
        ll ans=0;
        bool b=1;
        for (int i=0; i<M; i++) {
            if (a[i]<=ans+1) {
                ans+=a[i];
                if (ans>=N) break;
            }else {b=0; break;};
        }
        if (b && ans>=N) printf("Case #%d: Wow\n", tt);
        else printf("Case #%d: Nah\n", tt);
    }
}