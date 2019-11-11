#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#define INT_MAX 2147483647
using namespace std;

bool isN[50000];
vector<int> num;

int getN(int, int);

int main(){
    //freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i=2; i<=trunc(sqrt(INT_MAX)); i++){
        if (!isN[i]){
            num.push_back(i);
            for (int j=i+i; j<=trunc(sqrt(INT_MAX)); j+=i) isN[j]=1;
        }
    }
    //for (int i=0; i<20; i++) printf("%d ", num[i]);
    while (n!=0){
        int a0, b0, a1, b1;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        int ans=1;
        bool disN=0;
        for (int i=0; i<num.size() && num[i]<=b1; i++) if (b1%num[i]==0){
            disN=1;
            int p=num[i],
                ma0=getN(a0, p),
                ma1=getN(a1, p),
                mb0=getN(b0, p),
                mb1=getN(b1, p),
                cnt=0;
            if (ma0>ma1 && mb0==mb1 &&(ma1<mb1 || ma1==mb1)) cnt=1;
            if (mb0<mb1 && ma0==ma1 && (ma1<mb1 || ma1==mb1)) cnt=1;
            if (ma0>ma1 && mb0<mb1 && ma1==mb1) cnt=1;
            if (ma0==ma1 && mb0==mb1 && (ma1<mb1 || ma1==mb1)) cnt=mb1-ma1+1;
            //printf("%d %d %d %d %d %d\n", p, ma0, ma1, mb0, mb1, cnt);
            ans*=cnt;
            if (ans==0) break;
        }
        if (b1!=1 && !disN){
            int p=b1,
                ma0=getN(a0, p),
                ma1=getN(a1, p),
                mb0=getN(b0, p),
                mb1=getN(b1, p),
                cnt=0;
            if (ma1>mb1 || ma0<ma1 || mb0>mb1) cnt=0;
            else if ((ma0>ma1 && mb0==mb1) || (mb0<mb1 && ma0==ma1)) cnt=1;
            else  if (ma0==ma1 && mb1==mb0) cnt=mb1-ma1+1;
            ans*=cnt;
        }
        printf("%d\n", ans);
        n--;
    }
}

int getN(int a, int b){
    int ans=0;
    while (a%b==0){
        a/=b;
        ans++;
    }
    return ans;
}