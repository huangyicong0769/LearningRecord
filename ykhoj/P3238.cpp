#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char ddata[2200000];
int p[2200000];

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int ttt=0;
    while (1){
        char ch=0;
        int N=0;
        ddata[N++]='~';
        ddata[N++]='#';
        for (ch=getchar(); ch>='a' && ch<='z'; ch=getchar()){
            ddata[N++]=ch;
            ddata[N++]='#';
        }
        if (ch=='E')
            break;
        int mid=0, r=0, ans=0;
        for (int i=1; i<N; i++){
            if (i<r) p[i]=min(p[mid*2-i], r-i);
            else p[i]=1;
            while (ddata[i-p[i]]==ddata[i+p[i]]) p[i]++;
            if (p[i]+i>r){
                r=p[i]+i;
                mid=i;
            }
            if (p[i]>ans) ans=p[i];
        }
        printf("Case %d: %d\n", ++ttt, ans-1);
    }
}