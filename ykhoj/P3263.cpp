/*
    Addition Chains
    POJ2248
    bailian.openjudge 2248
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int ans, a[105], N, m, tot;
bool b[105];

bool dfs(int);
inline void out();
inline void init();

int main(){
    for (scanf("%d", &N); N != 0; out(), scanf("%d", &N)) for (init(), m=1; dfs(2); m++) init();
}

bool dfs(int k){
    if (k>m) return a[m]==N?false:true;
    for (register int i=k-1; i>0; i--) for (register int j=i; j>0; j--){
        if (b[a[i]+a[j]] || a[i]+a[j]>N ) continue;
        if (a[i]+a[j]<=a[k-1]) return true;
        b[a[i]+a[j]]=true;
        a[k]=a[i]+a[j];
        if (!dfs(k+1)) return false;
        b[a[i]+a[j]]=false; 
    }
}

inline void out(){
#ifdef CH
    for (register int i=1; i<=m; i++) printf("%d ", a[i]); printf("\n");
#else
    printf("%d\n", m);
#endif
}

inline void init(){
    memset(b, 0, sizeof(b));
    b[1]=1;
    a[1]=1;
}