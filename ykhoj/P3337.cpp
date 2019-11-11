#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long ull; 

const int P=131;

ull s[1001000], p[1001000];
int sa[1001000], N;

int maxPrefixtion(int, int);
bool myComp(const int&, const int&);

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    N=1; p[0]=1;
    for (char ch=getchar(); ch>='a' && ch<='z'; ch=getchar(), N++){
        s[N]=s[N-1]*P+ch-'a';
        p[N]=p[N-1]*P;
        sa[N]=N;
    }
    sort(sa+1, sa+N, myComp);
    for (int i=1; i<N; i++) printf("%d ", sa[i]-1); printf("\n");
    for (int i=1; i<N; i++) printf("%d ", maxPrefixtion(sa[i], sa[i-1])); printf("\n");
    return 0;
}

int maxPrefixtion(int x, int y){
    int l=0, r=N-max(x, y), ans=0;
    while (l<=r){
        int mid=(l+r)/2;
        if (s[x+mid-1]-s[x-1]*p[mid] == s[y+mid-1]-s[y-1]*p[mid]) {
            l=mid+1;
            ans=mid;
        }else r=mid-1;
    }
    return ans;
}

bool myComp(const int& x, const int& y){
    int maxPf=maxPrefixtion(x, y);
    if (y+maxPf>=N) return 0;
    if (x+maxPf>=N || s[x+maxPf]-s[x+maxPf-1]*p[1]<s[y+maxPf]-s[y+maxPf-1]*p[1]) return 1; else return 0;
}