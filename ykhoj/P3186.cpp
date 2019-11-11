#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

double r[100010];

int main(){
    //freopen("input.txt", "r", stdin);
    int n; double a, b, d;
    scanf("%lf%lf%lf%d", &a, &b, &d, &n);
    for (int i=0; i<n; i++){
        double x, y;
        scanf("%lf%lf", &x, &y);
        r[i]=a*x+b*y;
    }
    sort(r, r+n);
    int D=d*sqrt(a*a+b*b);
    int ans=0, j=0;
    for (int i=0; i<n; i++){
        while (j<n && r[j]-r[i]<=2*D) j++;
        ans=max(ans, j-i);
    }
    printf("%d\n", ans);
}