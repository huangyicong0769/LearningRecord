/*
BZOj4004 
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#define reg register
#define f(a, b, c) for (reg int a=b; a<c; a++)
using namespace std;

const double eps=1e-8;

long double a[510][510];
int c[510], N, M, ans1, ans2;

int main(){
    scanf("%d%d", &N, &M);
    f (i, 0, N) f (j, 0, M) {
        double t;
        scanf("%lf", &t);
        a[i][j]=t;
    }
    f (i, 0, N) scanf("%d", &c[i]);
    int ans1=0, ans2=0;
    f (i, 0, M){
        int now=-1;
        f (j, ans1, N){
            if (fabs(a[j][i])>eps && (now==-1 || c[now]>c[j])) now=j;
        }
        if (now==-1) continue;
        f (j, 0, M) swap(a[ans1][j], a[now][j]);
        swap(c[now], c[ans1]);
        ans2+=c[ans1];
        f (j, 0, N) if (ans1!=j && fabs(a[j][i])>eps){
            long double r=a[j][i]/a[ans1][i];
            f (k, i, M) a[j][k]-=r*a[ans1][k];
        }
        ans1++;
    }
    printf("%d %d\n", ans1, ans2);
}