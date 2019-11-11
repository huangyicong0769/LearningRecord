#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int a[100010], b[1000100];

int main(){
    //freopen("input.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for (int i=1; i<=N; i++){
        scanf("%d", &a[i]);
        b[a[i]]++;
    }
    for (int i=1; i<=N; i++){
        int ans=0;
        for (int j=1; j<=trunc(sqrt(a[i])); j++){
            if (a[i]%j==0){
                if (a[i]/j==j) ans+=b[j];
                else ans+=b[j]+b[a[i]/j];
            }
        }
        printf("%d\n", ans-1);
    }
}