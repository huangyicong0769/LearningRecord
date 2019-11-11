#include <iostream>
#include <queue>
#include <cstdio>
#define IMAX 2147483647
using namespace std;

int N, T;

priority_queue<int, vector<int>, greater<int> > myHeap;

bool check(const int&);

int main(){
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
    #endif // DEBUG
    scanf("%d%d", &N, &T);
    for (int i=0; i<N; i++){
        int a;
        scanf("%d", &a);
        myHeap.push(a);
    }
    int l=1, r=N;
    while(l<r){
        #ifdef DEBUG
            //printf("%d %d\n", l, r);
        #endif // DEBUG
        int mid=(l+r)/2;
        if (check(mid)) r=mid; else l=mid+1; 
    }
    printf("%d\n", r);
}

bool check(const int& K){
    priority_queue<int, vector<int>, greater<int> > t=myHeap;
    long long ans=0, cntt=0, cnttt=0;
    if (K-1!=0) cntt=(N-1)%(K-1)+1;
    cnttt=K-cntt;
    #ifdef DEBUG
        printf("%d===\n", K);
    #endif // DEBUG
    while (t.size()>1){
        long long cnt=0;
        #ifdef DEBUG
            printf("---\n");
        #endif // DEBUG
        for (int i=cnttt; i<K && t.size()>0; i++){
            cnt+=t.top();
            #ifdef DEBUG
                printf("%d\n", t.top());
            #endif // DEBUG
            t.pop();
        }
        cnttt=0;
        ans+=cnt;
        if (ans>IMAX) return false;
        t.push(cnt);
    }
    if (ans>T) return false; else return true;
}