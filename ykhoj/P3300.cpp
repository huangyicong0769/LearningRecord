#include <iostream>
#include <cstdio>
#include <cmath>
#define reg register
#define f(a, b, c) for (reg int a=b; a<c; a++)
using namespace std;

int N;
double c[20][20], b[20], a[20][20];

int main(){
    scanf("%d", &N);
    f(i, 0, N+1) f(j, 0, N) scanf("%lf", &a[i][j]);
    f(i, 0, N) f(j, 0, N) {
        c[i][j]=2*(a[i][j]-a[i+1][j]);
        b[i]+=a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j];
    }
    f(i, 0, N){
        f(j, i, N)
            if (fabs(c[j][i])>1e-8){
                f(k, 0, N) swap(c[i][k], c[j][k]);
                swap(b[i], b[j]);
            }
        f(j, 0, N){
            if (i==j) continue;
            double r=c[j][i]/c[i][i];
            f(k, i, N) c[j][k]-=c[i][k]*r;
            b[j]-=b[i]*r;
        }
    }
    f(i, 0, N) printf("%.3lf ", b[i]/c[i][i]); puts("");
}