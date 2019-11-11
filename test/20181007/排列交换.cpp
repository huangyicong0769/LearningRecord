#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int a[500100], num[500100];

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int N, K;
    scanf("%d%d", &N, &K);
    for (int i=1; i<=N; i++){
        scanf("%d", &a[i]);
        num[a[i]]=i;
    }
    if (N>1000 && K==1){
        sort(a, a+N);
        for (int i=1; i<=N; i++) printf("%d ", a[i]); printf("\n"); 
        return 0;
    }
    if (N>1000 && K==N-1){
        if (a[0]>a[N]) swap(a[0], a[N]);
        for (int i=1; i<=N; i++) printf("%d ", a[i]); printf("\n"); 
        return 0;
    }
    bool b=1;
    while (b){
        b=0;
        for (int i=N; i>1; i--){
            if (i+1<=N && num[i]-num[i+1]>=K) { 
                swap(num[i], num[i+1]);
                swap(a[num[i]], a[num[i+1]]);
                b=1;
            }
            if (num[i-1]-num[i]>=K){
                swap(num[i-1], num[i]);
                swap(a[num[i-1]], a[num[i]]);
                b=1;
            }
        }
    }
    for (int i=1; i<=N; i++) printf("%d ", a[i]); printf("\n"); 
}