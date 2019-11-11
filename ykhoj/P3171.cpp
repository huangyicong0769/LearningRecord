#include <iostream>
#include <cstdio>
using namespace std;

int a[5010], ans1=(1<<31)-1, ans2=(1<<31)-1;

int main(){
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        char c;
        cin>>c;
        if (c=='F') a[i]=1;
        else a[i]=0; 
    }
    for (int k=1; k<=n; k++){
        bool flag=1;
        int m=0, b[5010]={0};
        for (int i=0; i<n; i++){
            b[i]+=b[i-1];
            if ((a[i]+b[i])%2==0){
                if (i+k>n){
                    flag=0;
                    break;
                }
                b[i]++;
                b[i+k]++;
                m++;
            }
        }
        if (flag){
            if (ans1>m){
                ans1=m;
                ans2=k;
            }
        }
    }
    printf("%d %d\n", ans2, ans1);
}