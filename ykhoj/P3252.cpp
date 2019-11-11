#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#define P1 13331
#define P2 9999991
using namespace std;

typedef unsigned long long ull;

map<ull, int> h;
ull p1[1010], p2[1010], m1[1010][1010], m2[105][1005];

int main(){
    register int M, N, A, B, Q;
    scanf("%d%d%d%d", &M, &N, &A, &B);
    for (register int i=1; i<=M; i++) {
        char ch=getchar();
        while (ch!='0' && ch!='1') ch=getchar();
        for (register int j=1; j<=N; j++) m1[i][j]=ch-'0', ch=getchar();
    }
    p1[0]=p2[0]=1;
    for (register int i=1; i<=M; i++) p1[i]=p1[i-1]*P1;
    for (register int i=1; i<=N; i++) p2[i]=p2[i-1]*P2;
    for (register int i=1; i<=M; i++) for (register int j=1; j<=N; j++) m1[i][j]+=m1[i][j-1]*P1;
    for (register int j=1; j<=N; j++) for (register int i=1; i<=M; i++) m1[i][j]+=m1[i-1][j]*P2; 
    for (register int i=A; i<=M; i++) for (register int j=B; j<=N; j++) h[m1[i][j]-m1[i-A][j]*p2[A]-m1[i][j-B]*p1[B]+m1[i-A][j-B]*p2[A]*p1[B]]=1;
    scanf("%d", &Q);
    while (Q--){
        for (register int i=1; i<=A; i++) {
            char ch=getchar();
            while (ch!='0' && ch!='1') ch=getchar();
            for (register int j=1; j<=B; j++) m2[i][j]=ch-'0', ch=getchar();
        }
        for (register int i=1; i<=A; i++) for (register int j=1; j<=B; j++) m2[i][j]+=m2[i][j-1]*P1;
        for (register int j=1; j<=B; j++) for (register int i=1; i<=A; i++) m2[i][j]+=m2[i-1][j]*P2;
        if (h.count(m2[A][B])) printf("1\n");
        else printf("0\n");
    }
}
