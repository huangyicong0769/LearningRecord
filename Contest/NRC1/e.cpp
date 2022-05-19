#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

struct Name{
    string team, home;
}a[1005];
string ans[1005];

bool compareName(Name a, Name b){
    return a.team > b.team;
}

int main(){
    int n;
    scanf("%d", &n);
    set<string> teamSet;
    for (register int i = 0; i < n; i++){
        cin >> a[i].team >> a[i].home;
        teamSet.insert(a[i].team);

    }
    set<string> ansSet;
    for(register int i = 0; i < n; i++){
        string tmp = a[i].team;
        if (teamSet.count(a[i].team) > 1)
            tmp[2] = a[i].home[0];
        if (ansSet.find(tmp) != ansSet.end() && (tmp[2] = a[i].home[0]) && ansSet.find(tmp) != ansSet.end()) {
            puts("NO");
            return 0;
        }
        ans[i] = tmp;
        ansSet.insert(tmp);
    }
    puts("YES");
    for (register int i = 0; i < n; i++) cout << ans[i][0] << ans[i][1] << ans[i][2] << endl;
}