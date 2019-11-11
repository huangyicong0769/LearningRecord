#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const ll INF=1e15;

int s[1000][1000];

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N; 
    scanf("%d", &N);
    for (int i=1; i<=N; i++) for (int j=1; j<=N; j++) scanf("%d", &s[i][j]);
    for (int i=1; i<=N; i++) for (int j=1; j<=N; j++) s[i][j]+=s[i][j-1];
    ll ans=-1*INF;
    for (int y1=0; y1<N; y1++){
        for (int y2=y1+1; y2<=N; y2++){
            ll cnt1=-1, cnt2=-1*INF;
            for (int i=1; i<=N; i++){
                if (cnt1>0) cnt1+=s[i][y2]-s[i][y1];
                else cnt1=s[i][y2]-s[i][y1];
                cnt2=max(cnt2, cnt1);
            }
            ans=max(cnt2, ans);
        }
    }
    printf("%ld", ans);
}