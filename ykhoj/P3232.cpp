#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int N, s[25], top=0;
vector<string> out;

void dfs(int x, string o){
    if (out.size()>20) return;
    if (x>N){
        if (out.size()>20) return;
        for (int i=top-1; i>=0; i--)
            o+=static_cast<char>(s[i]+'0');
        out.push_back(o);
        return;
    }
    if (top>0){
        o+=static_cast<char>(s[--top]+'0'); 
        dfs(x, o);
        s[top++]=*(o.end()-1)-'0';
        o.erase(o.end()-1);
    }
    s[top++]=x;
    dfs(x+1,o);
    top--;
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    scanf("%d", &N);
    dfs(1, "");
    //sort(out.begin(), out.end());
    for (int i=0; i<min(20, (int)out.size()); i++) {
        for (int j=0; j<out[i].size(); j++) printf("%d", out[i][j]-'0');
        printf("\n");
    }
}