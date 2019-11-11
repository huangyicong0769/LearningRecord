#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char s[2][1000010], ts[2000010];

inline int mF(const int &, const int &);

int main(){
    scanf("%s", s[0]);
    scanf("%s", s[1]);
    const int L=strlen(s[0]),
              mS1=mF(0, L), mS2=mF(1, L);
    for (register int i=mS1, j=mS2, k=0; k<L; (i+=1)%=L, (j+=1)%=L, k++)
        if (s[0][i]!=s[1][j]) {
            printf("No\n");
            return 0;
        }
    printf("Yes\n");
    for (register int i=mS1, k=0; k<L; (i+=1)%=L, k++) printf("%c", s[0][i]); printf("\n");
}

inline int mF(const int & id, const int & len){
    for (register int i=0; i<len; i++) ts[i]=ts[i+len]=s[id][i];
    register int i=0, j=1, k;
    while (i<len && j<len){
        for (k=0; k<len && ts[i+k]==ts[j+k]; k++);
        if (k==len) break;
        if (ts[i+k]>ts[j+k]){
            i=i+k+1;
            if (i==j) i++;
        }else {
            j=j+k+1;
            if (i==j) j++;
        }
    }
    return min(i, j);
}