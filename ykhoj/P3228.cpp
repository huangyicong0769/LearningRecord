#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int t1[600], t2[600];
char s1[600], s2[600];

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int T; scanf("%d", &T);
    while (T--){
        memset(s2, 0, sizeof(s2));
        int a, b;
        scanf("%d%d%s", &a, &b, s1);
        int ns=strlen(s1);
        for (int i=ns-1; i>=0; i--) {
            t1[ns-1-i]=s1[i];
            if ('0'<=s1[i] && s1[i]<='9') t1[ns-1-i]-='0'; else
            if ('A'<=s1[i] && s1[i]<='Z') t1[ns-1-i]-='A'-10; else
            if ('a'<=s1[i] && s1[i]<='z') t1[ns-1-i]-='a'-36;
        }
        int nd=0;
        while (ns){
            for (int i=ns-1; i>0; i--){
                t1[i-1]+=t1[i]%b*a;
                t1[i]/=b;
            }
            t2[nd++]=t1[0]%b;
            t1[0]/=b;
            while (ns>0 && !t1[ns-1]) ns--;
        }
        for (int i=0; i<nd; i++) {
            s2[nd-i-1]=t2[i];
            if (0<=t2[i] && t2[i]<=9) s2[nd-i-1]+='0'; else
            if (10<=t2[i] && t2[i]<=35) s2[nd-i-1]+='A'-10; else
            if (36<=t2[i] && t2[i]<=61) s2[nd-1-i]+='a'-36;
        }
        printf("%d %s\n%d %s\n\n", a, s1, b, s2);
    }
}