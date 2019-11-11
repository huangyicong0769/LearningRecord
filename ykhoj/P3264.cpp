/*
    送礼物
    CH2401
    tyvj1340
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef long long ll;

ll W;
int N, G[50], ans=0;
vector<int> v;
set<int> s;

void dfs(int, ll, const int, const int);

int main(){
    scanf("%lld %d", &W, &N);
    for (register int i=0; i<N; G[i++]*=-1) scanf("%d", &G[i]);
    sort(G, G+N);
    dfs(0, 0, 0, N/2+1);
    sort(v.begin(), v.end());
    dfs(N/2+2, 0, N/2+2, N-1);
    printf("%d\n", ans);
}

void dfs(int x, ll w, const int L, const int R){
    if (-w>W) return;
    if (x>R){
        if (L==0) v.push_back(-w);
        else{
            int score=W+w, l=0, r=v.size()-1, cnt=0;
            while (l<r){
                int mid=(l+r+1)/2;
                if (v[mid]<=score){
                    l=mid;
                    cnt=v[mid];
                }else r=mid-1;
            }
            ans=max((ll)ans, cnt-w);
        }
        return;
    }
    dfs(x+1, w+G[x], L, R);
    dfs(x+1, w, L, R);
}