#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Node{
    int ti, val;
}game[1000];

bool isG[1000];

bool myComp(const Node& a, const Node& b){
    if (a.ti==b.ti) return a.val>b.val;
    else return a.ti>b.ti;
}

int main(){
    //freopen("input.txt", "r", stdin);
    int m, N, maxT=0;
    scanf("%d%d", &m, &N);
    for (int i=0; i<N; i++) scanf("%d", &game[i].ti);
    for (int i=0; i<N; i++) scanf("%d", &game[i].val);
    for (int i=0; i<N; i++) maxT=max(maxT, game[i].ti);
    sort(game, game+N, myComp);
    for (int i=maxT; i>0; i--){
        int k=-1, cnt=0;
        for (int j=0; j<N && (game[j].ti>i || game[j].ti==i); j++)
            if (!isG[j] && cnt<game[j].val){
                cnt=game[j].val;
                k=j;
            }
        if (k!=-1 && !isG[k]){
            isG[k]=1;
            //printf("%d %d %d\n", i,     k, game[k].val);
        }
    }
    for (int i=0; i<N; i++) if (!isG[i]) m-=game[i].val;
    printf("%d\n", m);
}