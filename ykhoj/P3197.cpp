#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int s[50000], a[50000];

int main(){
    //freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--){
        int N, K;
        scanf("%d%d", &K, &N);
        memset(s, 0, sizeof(s));
        for (int i=1; i<=N; i++){
            scanf("%d", &a[i]);
            s[i]=(s[i-1]+a[i])%K;
        }
        sort(s, s+N+1);
        int cnt=0, j=1;
        for (int i=0; i<=N;){
            while (s[i]==s[j]) j++;
            cnt+=(long long)(j-i)*(j-i-1)/2;
            i=j;
            j=i+1;
        }
        printf("%d\n", cnt);
    }
}