#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

ll X[1010], Y[1010], Z[1010], N, H, R;

bool b[1010], fi;

double sqr(double);
double dist(const int&, const int&);
void dfs(const int&);

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int T;
    scanf("%d", &T);
    while (T--){
        memset(b, 0, sizeof(b));
        scanf("%lld%lld%lld", &N, &H, &R);
        for (int i=0; i<N; i++) scanf("%lld%lld%lld", &X[i], &Y[i], &Z[i]);
        fi=0;
        for (int i=0; i<N; i++) if (Z[i]<=R && !fi)
            dfs(i);
        if (fi) printf("Yes\n");
        else printf("No\n");
    }
}

double sqr(double x){
    return x*x;
}

double dist(const int& i, const int& j){
    return sqrt(sqr(X[i]-X[j])+sqr(Y[i]-Y[j])+sqr(Z[i]-Z[j]));
}

void dfs(const int& x){
    if (Z[x]>=H-R){
        fi=1;
        return;
    }
    b[x]=1;
    for (int i=0; i<N; i++) if (!b[i] && dist(x, i)<=2*R)
        dfs(i);
}