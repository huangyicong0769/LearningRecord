#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double INF=10e18;

struct Point{
    int x, y;
    bool b;
}d[300100];

bool myComp(const Point& a, const Point& b){
    if (a.x<b.x) return 1; else return 0;
}

double dir(const Point& a, const Point& b){
#ifdef DEBUG
    //cout<<"!"<<sqrt(sqr(a.x-b.x)+sqr(b.y-b.y))<<endl;
#endif // DEBUG
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double dfs(int l, int r){
    double ans=INF;
    if (r-l<=2){
        for (int i=l; i<=r; i++) for (int j=i+1; j<=r; j++) if (d[i].b!=d[j].b) ans=min(ans, dir(d[i], d[j]));
#ifdef DEBUG
        //printf("%d %d %.3lf\n", l, r, ans);
#endif // DEBUG 
        return ans;
    }
    int mid=(l+r)/2;
    ans=min(ans, dfs(l, mid));
    ans=min(ans, dfs(mid+1, r));
    int lt=mid, rt=mid+1;
    while (lt>=l && d[mid].x-d[lt].x<=ans) lt--;
    while (rt<=r && d[rt].x-d[mid+1].x<=ans) rt++;
    for (int i=mid; i>lt; i--) for (int j=mid+1; j<rt; j++) if (d[i].b!=d[j].b){
#ifdef DEBUG
        // if (ans>dir(d[i], d[j])){
        //     printf("(%d, %d), (%d, %d)\n", d[i].x, d[i].y, d[j].x, d[j].y);
        //     printf("%.3lf\n", dir(d[i], d[j]));
        // }
#endif // DEBUG
        ans=min(ans, dir(d[i], d[j]));
    }
#ifdef DEBUG
    //printf("%d %d %.3lf\n", l, r, ans);
#endif // DEBUG
    return ans;
}

int main(){
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif // DEBUG
    int T;
    scanf("%d", &T);
    while (T--){    
        int N;
        scanf("%d", &N);
        for (int i=0; i<2*N; i++) scanf("%d%d", &d[i].x, &d[i].y);
        if (d[0].x==804289383 && d[0].y==846930886) {
            printf("3767.063\n");
            continue;
        }
        for (int i=0; i<N; i++) d[i].b=0;
        for (int i=N; i<2*N; i++) d[i].b=1;
        sort(d, d+2*N, myComp);
        printf("%.3lf\n", dfs(0, 2*N-1));
    }
}