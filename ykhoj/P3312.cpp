#include <iostream>
#include <cstdio>
#include <cstring>
#define reg register
#define f(a, b, c) for (reg int a=b; a<=c; a++)
using namespace std;

int sg[210][210], N, M;

inline int SG(int, int);

int main(){
    memset(sg, -1, sizeof(sg));
    sg[2][2]=sg[2][3]=sg[3][2]=0;
    while (cin>>N>>M) 
        if (SG(N, M)==0) puts("LOSE");
        else puts("WIN");
}

inline int SG(int x, int y){
    if (sg[x][y] != -1) return sg[x][y];
	bool f[210];
	memset(f, 0, sizeof(f));
    f (i, 2, x-i) f[SG(i, y)^SG(x-i, y)]=1;
    f (i, 2, y-i) f[SG(x, i)^SG(x, y-i)]=1;
    reg int t=0;
    while (f[t]) ++t;
    return sg[x][y]=t;
}