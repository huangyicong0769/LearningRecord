#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

typedef long long ll;

struct trieNode{
    int children[2];
}ORIGIN;

class Trie{
    protected:
    vector<trieNode> _value;
    public:
    Trie();
    inline void insert(int);
    inline int check(int);
};

int ans, root, d[100100];
bool visit[100100];
vector<int> vEdge[100100], vPoint[100100];

void workD(const int&);
inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N; root=-1;
    while (scanf("%d", &N)!=EOF){
        for (int i=1; i<N; i++){
            int a=read(), b=read(), c=read();
            if (root==-1) root=a;
            vPoint[a].push_back(b);
            vEdge[a].push_back(c);
            vPoint[b].push_back(a);
            vEdge[b].push_back(c);
        }
        ans=0; visit[root]=1;
        Trie trie;
        trie.insert(0);
        workD(root);
        for (int i=0; i<N; i++){
            ans=max(ans, trie.check(d[i]));
            trie.insert(d[i]);
        }
        printf("%d\n", ans);
        memset(visit, 0, sizeof(visit));
        memset(d, 0, sizeof(d));
        for (int i=0; i<N; i++) vEdge[i].clear(), vPoint[i].clear();
    }
    return 0;
}

void workD(const int& x){
    for (int i=0; i<vPoint[x].size(); i++){
        int j=vPoint[x][i];
        d[j]=d[x]^vEdge[x][i];
        if (visit[j]) continue;
        visit[j]=1;
        workD(j);
    }
}

Trie::Trie(){
    _value.push_back(ORIGIN);
}

inline void Trie::insert(int a){
    //cout<<"Inserting"<<a<<endl;
    int now=0;
    ll t=1LL<<31;
    for (int i=0; i<32; i++){
        int ch=a/t; 
        //cout<<"  "<<ch<<" "<<now<<" ";
        a%=t;
        t>>=1;
        if (_value[now].children[ch]) now=_value[now].children[ch];
        else{
            _value[now].children[ch]=_value.size();
            now=_value.size(); //cout<<_value.size();
            _value.push_back(ORIGIN);
        }
        //cout<<endl;
    }
}

inline int Trie::check(int a){
    //cout<<"Checking"<<a<<endl;
    int re=0, now=0;
    ll t=1LL<<31;
    for (int i=0; i<32; i++){
        int ch=a/t; 
        //cout<<"  "<<ch<<" "<<now<<endl;
        a%=t;
        t>>=1;
        re<<=1;
        if (_value[now].children[!ch]) {
            now=_value[now].children[!ch];
            re++;
        }
        else if (_value[now].children[ch]) now=_value[now].children[ch];
        else return 0;
    }
    //cout<<re<<endl;
    return re;
}

inline int read(){
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') {
        x=x*10+(ch-'0');
        ch=getchar();
    }
    return x;
}