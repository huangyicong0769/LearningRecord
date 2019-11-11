#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

int N, K, fast[65];
vector<int> v[65];

inline int readN();
inline bool check(const int&);

int main(){
    N=readN(); K=readN();
    for (int i=0; i<K; i++)
        for (int j=0, T=readN(); j<T; j++) v[i].push_back(readN());
    int l=1, r=(1<<31)-1, ans=-1;
    while (l<=r){
        int mid=(static_cast<long long>(l)+r)/2;
        if (check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
        //cout<<l<<' '<<r<<endl;
    }
    printf("%d\n", ans);
}

inline int readN(){
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

inline bool check(const int &mL){
    //cout<<mL<<"===================\n";
    memset(fast, 0, sizeof(fast));
    for (int i=0; i<v[0].size(); i++){
        int maxn=v[0][i], minn=v[0][i];
        bool b=1;
        for (int j=1; j<K; j++){
            b=0;
            int k=fast[j];
            while (maxn-v[j][k]>mL) k++;
            fast[j]=k;
            if ( k<v[j].size() && v[j][k]-minn<=mL){
                if (minn-v[j][k]>0)  minn=v[j][k];
                else  if (v[j][k]-maxn>0) maxn=v[j][k];
                b=1;
                k++;
            }
            if (b==0) break;
        }
        if (b) return true;
    }
    return false;
}