#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct Node{
    int d, p;
};

vector<int> v1[1000100];
set<int> s[1000100], s1[1000100];

bool b[1000100];

int main(){
    freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    const int N=n;
    for (int i=0; i<m; i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (u==v) continue;
        if (s[u].count(v)>0) continue;
        if (w==2){
            if (s1[u].count(v));
            n++;
            s[u].insert(n);
            v1[u].push_back(n);
            s[n].insert(v);
            v1[n].push_back(v);
            s1[u].insert(v);
        }else{
            s[u].insert(v);
            v1[u].push_back(v);
        }
    }
    queue<Node> q;
    Node f; f.d=0; f.p=1;
    q.push(f);
    b[1]=1;
    while (!q.empty()){
        Node x=q.front(); q.pop();
        int p=x.p, d=x.d;
        for (int i=0; i<v1[p].size(); i++){
            int j=v1[p][i];
            if (j==N){
                printf("%d\n", d+1);
                return 0;
            }
            if (!b[j]){
                b[j]=1;
                Node l; l.p=j; l.d=d+1;
                q.push(l);
            }
        }
    }
}