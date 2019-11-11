#include <iostream>
#include <cstdio>
using namespace std;

int N, A[100100], B[100100], C[100100];

double cnt(const double&);

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int T;
    scanf("%d", &T);
    while (T--){
        scanf("%d", &N);
        for (int i=0; i<N; i++) scanf("%d%d%d", &A[i], &B[i], &C[i]);
        double l=0.0, r=1000.0;
        for (int i=0; i<100; i++){
            double lm=(l+l+r)/3,
                   rm=(l+r+r)/3;
            if (cnt(lm)<cnt(rm)) r=rm;
            else l=lm;
        }
        printf("%.4lf\n", cnt(l));
    }
}

double cnt(const double& X){
    double ans=-(1e18);
    for (int i=0; i<N; i++)
        ans=max(ans, A[i]*X*X+B[i]*X+C[i]);
    return ans;
}