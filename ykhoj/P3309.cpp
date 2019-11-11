#include <iostream>
#include <cstdio>
#define reg register
#define f(a, b, c) for (reg int a=b; a<c; a++)
using namespace std;

int N, a[100010], b[100010];
double ans1=0, ans2=0, ans3=0;

inline void deal(const int &);

int main(){
    scanf("%d", &N);
    f (i, 1, N+1) scanf("%d", &a[i]);
    f (i, 0, 32) deal(i);
    printf("%.3lf %.3lf %.3lf\n", ans1, ans2, ans3); 
}

inline void deal(const int & x){
    int c1=0, c2=0, la[2]={0};
    double f=(double)(1<<x) /N /N;
    f (i, 1, N+1){
        b[i]=((a[i]>>x)&1);
        if (b[i]){
            ans1+=f;
            ans2+=f;
            ans3+=f;
        }
        if (!b[i]) ans1+=c2*2*f, ans3+=la[1]*2*f;
        else {
            ans1+=c1*2*f;
            ans2+=(i-1-la[0])*2*f;
            ans3+=(i-1)*2*f;
        }
        c1++;
        if (b[i]) swap(c1, c2);
        la[b[i]]=i;
    }
}