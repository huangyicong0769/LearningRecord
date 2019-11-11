#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int M, N, m[1001000], X[1001000], mNum;

bool check(int);

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i=0; i<N; i++)
        scanf("%d", &X[i]);
    sort(X, X+N);
    int l=0, r=X[N-1]-X[0];
    while(l<r){
        int mid=(l+r+1)/2;
        if (check(mid)) l=mid; else r=mid-1;
    }
    printf("%d\n", l);
}

bool check(int d){
    int cnt=M, k=-1;
    for (int i=0; i<N; i++){
        if (k==-1 || X[i]-X[k]>=d){
            k=i;
            cnt--;
            if (cnt<=0) return true;
        }
    }
    return false;
}