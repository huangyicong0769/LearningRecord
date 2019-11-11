#include <iostream>
#include <cstdio>
using namespace std;

char s[10010][80];
int R, C, nex[10010];

inline bool checkH(const int &, const int &);
inline bool checkW(const int &, const int &);
inline int nexH();
inline int nexW();

int main(){
    scanf("%d%d", &R, &C);
    for (register int i=1; i<=R; i++) scanf("%s", s[i]+1);
    printf("%d\n", nexH()*nexW());
}

inline bool checkW(const int & x, const int & y){
    for (register int i=1; i<=R; i++) if (s[i][x]!=s[i][y]) return false;
    return true;
}

inline bool checkH(const int & x, const int &y){
    for (register int i=1; i<=C; i++) if (s[x][i]!=s[y][i]) return false;
    return true;
}

inline int nexH(){
    nex[1]=0;
    for (register int i=2, j=0; i<=R; i++){
        while (j>0 && !checkH(i, j+1)) j=nex[j];
        if (checkH(i, j+1)) j++;
        nex[i]=j;
    }
    return R-nex[R];
}

inline int nexW(){
    nex[1]=0;
    for (register int i=2, j=0; i<=C; i++){
        while (j>0 && !checkW(i, j+1)) j=nex[j];
        if (checkW(i, j+1)) j++;
        nex[i]=j;
    }
    return C-nex[C];
}