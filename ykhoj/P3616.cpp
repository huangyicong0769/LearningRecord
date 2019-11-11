#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int N;
    scanf("%d", &N);
    string s[3];
    for (int i=0; i<3; i++) cin>>s[i];
    string anss;
    for (int i=0; i<3; i++){
        anss=s[i];
        #ifdef DEBUG
        cout<<i<<" "<<anss<<endl;
        #endif // DEBUG
        for (int i=0, j=anss.size()-1; i<j; i++, j--) swap(anss[i], anss[j]);
        #ifdef DEBUG
        cout<<anss<<endl;
        #endif // DEBUG
        for (int j=0; j<3; j++) if (i!=j){
            int cnt=s[j][0]-anss[0];
            if (cnt<0) cnt+=26;
            if (cnt>6) continue;
                        #ifdef DEBUG
            printf("  %d ", cnt);
            cout<<s[j]<<endl;
            #endif // DEBUG
            bool isR=1;
            for (int k=0; k<s[j].size(); k++) {
                int t=s[j][k]-anss[k];
                if (t<0) t+=26;
                if (t!=cnt) {
                    isR=0;
                    break;
                }
            }
            if (!isR) continue;
            for (int k=0; k<3; k++) if (i!=k && j!=k){
                int cntt=anss[0]-s[k][0];
                isR=0;
                if (cntt<0) cntt+=26;
                if (cntt!=cnt) continue;
                #ifdef DEBUG
                cout<<"    "<<cntt<<" "<<s[k]<<endl;
                #endif // DEBUG
                isR=1;
                for (int l=0; l<s[k].size(); l++) {
                    int t=anss[l]-s[k][l];
                    if (t<0) t+=26;
                    if (t!=cntt){
                        isR=0;
                        break;
                    } 
                }
            }
            if (!isR) continue;
            #ifdef DEBUG
            cout<<"!";
            #endif // 
            cout<<anss<<endl;
            return 0;
        }
    }
}