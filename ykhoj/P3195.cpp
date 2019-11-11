#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[1000][1000], f[1000][1000], s1[1000][1000], s2[1000][1000];

int main(){
    //freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--){
        int N;
        scanf("%d", &N);
        memset(f, 0, sizeof(f));
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        for (int i=0; i<N; i++) for (int j=0; j<N; j++){
            scanf("%d", &a[i][j]);
            s1[i][j]=s1[i][j-1]+a[i][j];
            s2[i][j]=s2[i-1][j]+a[i][j];
        }
        if (a[0][0]%2==0) f[0][0]=1;
        for (int i=0; i<N; i++)
        for (int j=0; j<N; j++){
            if (s1[i][j]%2==1 && s2[i][j]%2==0 && f[i][j-1]==0) f[i][j]=1;
            if (s1[i][j]%2==0 && s2[i][j]%2==1 && f[i-1][j]==0) f[i][j]=1;
            if (s1[i][j]%2==0 && s2[i][j]%2==0 && (f[i-1][j]==0 || f[i][j-1]==0)) f[i][j]=1;
        }
        if (f[N-1][N-1]) printf("W\n"); else printf("L\n");
    }
}