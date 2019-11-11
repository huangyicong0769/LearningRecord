#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int A[1001000], B[1001000], sum[1001000], f[1001000];

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int Q;
    while (scanf("%d", &Q)!=EOF){
        int ta=1, tb=1;
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        memset(sum, 0, sizeof(sum));
        memset(f, 0, sizeof(f));
        f[0]=-((1<<31)-1);
        for (int i=0; i<Q; i++){
            char c;
            cin>>c;
            if (c=='I'){
                int t;
                scanf("%d", &t);
                sum[ta]=sum[ta-1]+t;
                f[ta]=max(f[ta-1], sum[ta]);
                A[ta++]=t;
            }else if (c=='D' && ta>1) ta--; 
            else if (c=='L' && ta>1) B[tb++]=A[--ta];
            else if (c=='R' && tb>1) {
                sum[ta]=sum[ta-1]+B[--tb];
                f[ta]=max(f[ta-1], sum[ta]);
                A[ta++]=B[tb];
            }else if (c=='Q'){
                int t;
                scanf("%d", &t);
                printf("%d\n", f[t]);
            }
            // printf("1: "); for (int j=0; j<ta; j++) printf("%d ", A[j]); printf("\n");
            // printf("2: "); for (int j=0; j<ta; j++) printf("%d ", sum[j]); printf("\n");
            // printf("3: "); for (int j=0; j<ta; j++) printf("%d ", f[j]); printf("\n");
        }
    }
}