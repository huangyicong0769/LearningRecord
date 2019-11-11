#include <iostream>
#include <cstdio>
using namespace std;

int N;

double a[200100];

double cnt(const double&);

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    scanf("%d", &N);
    for (int i=0; i<N; i++) scanf("%lf", &a[i]);
    double l=-20000, r=20000;
    for (int ti=0; ti<300; ti++){
        double lm=(l+l+r)/3, rm=(l+r+r)/3;
        if (cnt(lm)<=cnt(rm)) r=rm;
        else l=lm;
    }
    printf("%.6lf\n", cnt(l));
}

double cnt(const double& x){
    double mins=0, maxs=0, sum=0, ans=0;
    for (int i=0; i<N; i++){
        sum+=a[i]-x;
        ans=max(ans, maxs-sum);
        ans=max(ans, sum-mins);
        maxs=max(maxs, sum);
        mins=min(mins, sum);
    }
    return ans;
}