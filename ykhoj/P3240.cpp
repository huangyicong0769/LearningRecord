#include <iostream>
#include <cstdio>
#include <vector>
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
    void insert(int);
    int check(int);
};

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    Trie trie;  
    int N=read(), ans=0;
    for (int i=0; i<N; i++){
        int a=read();
        if (i!=0) ans=max(ans, trie.check(a));
        trie.insert(a);
    }
    printf("%d\n", ans);
}

Trie::Trie(){
    _value.push_back(ORIGIN);
}

void Trie::insert(int a){
    //printf("Inserting %d\n", a);
    int now=0;
    ll t=1LL<<31;
    for (int i=0; i<32; i++){
        int ch=(t==0?1:a/t); 
        a%=t;
        //cout<<i<<" "<<t<<" "<<ch<<" "<<a<<endl;
        t>>=1;
        if (_value[now].children[ch]) now=_value[now].children[ch];
        else{
            _value[now].children[ch]=_value.size();
            now=_value.size();
            _value.push_back(ORIGIN);
        }
    }
}

int Trie::check(int a){
    //printf("Checking %d\n", a);
    int re=0, now=0;
    ll t=1LL<<31;
    for (int i=0; i<32; i++){
        int ch=(t==0?1:a/t); 
        //cout<<i<<" "<<t<<" "<<ch<<" "<<a<<endl;
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
    int x=0, f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}