#include <iostream>
#include <cstdio>
using namespace std;

int s[200100], e[200100], d[200100], N;

bool check(int p){
    int cnt=0;
    for (int i=0; i<N; i++){
        if (e[i]<p) cnt+=(e[i]-s[i])/d[i]+1;
        if (s[i]<=p && p<=e[i]) cnt+=(p-s[i])/d[i]+1;
    }
    return cnt%2;
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int T;
    for (scanf("%d", &T); T; T--){
        scanf("%d", &N);
        int l=1, r=-1, p=-1;
        for (int i=0; i<N; i++) {
            scanf("%d%d%d", &s[i], &e[i], &d[i]);
            r=max(r, e[i]);
        }
        while (l<=r){
            int mid=(l+r)/2;
            if (check(mid)){
                p=mid;
                r=mid-1;
            }else l=mid+1;
        }
        if (p==-1) printf("There's no weakness.\n");
        else {
            int c=0;
            for (int i=0; i<N; i++) if (s[i]<=p && p<=e[i] && (p-s[i])%d[i]==0) c++;
            printf("%d %d\n", p, c);
        }
    }
}