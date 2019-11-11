#include <iostream>
#include <cstdio>
using namespace std;

typedef unsigned long long ull;

const int P=131,
          SIZE=1000010;

char s[SIZE];
ull p[SIZE], f[SIZE];

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    p[0]=1;
    int i=1;
    for (char ch=getchar(); ch>='a' && ch<='z'; ch=getchar(), i++){
        p[i]=p[i-1]*P;
        f[i]=f[i-1]*P+ch-'a'+1;
    }
    int N=read();
    for (int i=0; i<N; i++){
        int l1=read(), r1=read(),
            l2=read(), r2=read();
        if (f[r1]-f[l1-1]*p[r1-l1+1]==f[r2]-f[l2-1]*p[r2-l2+1]) puts("Yes"); 
        else puts("No");
    }
}

inline int read(){
    int a=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9'){
        (a*=10)+=ch-'0';
        ch=getchar();
    }
    return a;
}