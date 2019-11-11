#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Node{
    int ti, pos;
}A[1010], B[1010], AA[1010], BB[1010];

bool isP[1010];

vector<int> a, b;

bool myComp(const Node& a, const Node& b){
    return a.ti<b.ti;
}

int main(){
    //freopen("input.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d", &A[i].ti);
        A[i].pos=i;
        AA[i]=A[i];
    }
    for (int i=0; i<N; i++){
        scanf("%d", &B[i].ti);
        B[i].pos=i;
        BB[i]=B[i];
    }
    sort(A, A+N, myComp);
    sort(B, B+N, myComp);
    //for (int i=0; i<N; i++) printf("%d ", AA[i].ti); printf("\n");
    //for (int i=0; i<N; i++) printf("%d ", BB[i].ti); printf("\n");
    for (int i=0, j=0; i<N || j<N; ){
        while (isP[A[i].pos] && i<N) i++;
        while (!isP[A[i].pos] && (A[i].ti<B[j].ti || A[i].ti==B[j].ti) && i<N){
            isP[A[i].pos]=1;
            a.push_back(A[i].pos);
            i++;
        }
        while (isP[B[j].pos] && j<N) j++;
        while (!isP[B[j].pos] && B[j].ti<A[i].ti && j<N){
            isP[B[j].pos]=1;
            b.push_back(B[j].pos);
            j++;
        }
    }
    int ans=0, at=0;
    for (int i=b.size()-1; i>=0; i--) a.push_back(b[i]);
    //for (int i=0; i<a.size(); i++) printf("%d ", a[i]); printf("\n");
    for (int i=0; i<a.size(); i++)
        at+=AA[a[i]].ti;
    //for (int i=0; i<N; i++) printf("%d ", at[i]); printf("\n");
    for (int i=0; i<a.size(); i++){
        ans-=AA[a[i]].ti;
        if (ans<0) ans=0;
        ans+=BB[a[i]].ti;
    }
    printf("%d\n", ans+at);
}