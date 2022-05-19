#include <iostream>
#include <string>
using namespace std;

bool solve(){
    int cntA[128] = {0}, cntB[128] = {0};
    int n, k;
    string a, b;
    cin >> n >> k >> a >> b;
    for(auto i : a) cntA[i] ++;
    for(auto i : b) cntB[i] ++;
    for (register int i = 'a'; i < 'z'; i++){
        if (cntA[i] < cntB[i]) return 0;
        cntA[i + 1] += (cntA[i] - cntB[i])/k*k;
    }
    return cntA['z'] == cntB['z'];
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--)
        if (solve()) puts("YES");
        else puts("NO");
}