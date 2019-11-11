#include <iostream>
#include <cstdio>
using namespace std;

char s[1000100];
int p[1000100];

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N, T=0;
    while(1){
        scanf("%d", &N);
        if (N==0) break;
        char ch=getchar();
        while (ch<'a' || ch>'z') ch=getchar();
        for (int i=1; i<=N; i++, ch=getchar()) s[i]=ch;
        p[1]=0;
        for (int i=2, j=0; i<=N; i++){
            while (j>0 && s[j+1]!=s[i]) j=p[j]; 
            if (s[i]==s[j+1]) j++;
            p[i]=j;
        }
        printf("Test case #%d\n", ++T);
        for (int i=2; i<=N; i++){
            if (i%(i-p[i])==0 && i/(i-p[i])>1)
                printf("%d %d\n", i, i/(i-p[i]));
        }
        printf("\n");
    }
}