//luogu  P2862
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Node{
    int x, y;
}px[511], py[511];

int C, N;

bool myComp1(const Node& a, const Node& b){
    return a.x<b.x;
}

bool myComp2(const Node& a, const Node& b){
    return a.y<b.y;
}

bool check(const int& a){
    int xe=0;
    for (int xs=0; xs<N; xs++){
        while (px[xe].x-px[xs].x<=a && xe<N) xe++;
        int ye=0;
        xe--;
        for (int ys=0; ys<N; ys++){
            int cnt=0;
            while (py[ye].y-py[ys].y<=a && ye<N){
                if (px[xs].x<=py[ye].x && py[ye].x<=px[xe].x) cnt++;
                //printf("%d\n", cnt); 
                ye++;
            }
            if (cnt>=C) return 1; 
        }
    }
    return 0;
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    scanf("%d%d", &C, &N);
    for (int i=0; i<N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        px[i].x=py[i].x=x;
        px[i].y=py[i].y=y;
    }
    sort(px, px+N, myComp1);
    sort(py, py+N, myComp2);
    int l=0, r=10010, ans=-1;
    while (l<=r){
        int mid=(l+r)/2;
        if (check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
    }
    printf("%d\n", ans+1);
}