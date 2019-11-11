#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int on[10];

int main(){
    freopen("input.txt", "r", stdin);
    int n, k, ans=200000000;
    scanf("%d%d", &n, &k);
    string os, anss;
    cin>>os;
    for (int i=0; i<n; i++) on[os[i]-'0']++;
    for (int i=0; i<10; i++){
        int tn=on[i], temp=0;
        string s=os;
        for (int l=1; l<10; l++){
            if (tn>=k) break;
            int ll=i+l;
            if (ll<10) for (int j=0; j<n; j++){
                if (s[j]==ll+'0') {
                    temp+=abs(ll-i);
                    s[j]=i+'0';
                    if (++tn>=k) break;
                }
            }
            if (tn>=k) break;
            ll=i-l;
            if (ll>=0) for (int j=n-1; j>=0; j--){
                if (s[j]==ll+'0'){
                    temp+=abs(i-ll);
                    s[j]=i+'0';
                    if (++tn>=k) break;
                }
            }
        }
        if (tn>=k && (temp<ans || temp==ans && anss>s)) {
            ans=temp;
            anss=s;
        }
    }
    cout<<ans<<endl<<anss<<endl;
}