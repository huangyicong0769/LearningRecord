#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct Node{
    int children[26]={0}, isWord=0;
}ORIGIN;

class Trie{
    protected:
        vector<Node> _v;
    public:
        Trie(){
            _v.push_back(ORIGIN);
        }
        void insert(const char* s, const int& N){
            int now=0;
            for (int i=0; i<N; i++){
                if (_v[now].children[s[i]-'a']) now=_v[now].children[s[i]-'a'];
                else {
                    _v[now].children[s[i]-'a']=_v.size();
                    now=_v.size();
                    _v.push_back(ORIGIN);

                }
            }
            _v[now].isWord++;
        }
        int prefix(const char* s, const int& N){
            int now=0, ans=0;
            for (int i=0; i<N; i++){
                if (_v[now].children[s[i]-'a']) now=_v[now].children[s[i]-'a'];
                else  return ans;
                ans+=_v[now].isWord;
            }
            return ans;
        }
};

char s[100];
int t=0;

inline int readStr(char* s){
    int n=0;
    char ch=getchar();
    while (ch<'a' || ch>'z') ch=getchar();
    while (ch>='a' && ch<='z') {
        s[n++]=ch;
        ch=getchar();
    }
    return n;
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int N, M;
    Trie trie;
    scanf("%d%d", &N, &M);
    for (int i=0; i<N; i++){    
        memset(s, 0, sizeof(s));
        t=readStr(s);
        trie.insert(s, t);
    }
    for (int i=0; i<M; i++){
        memset(s, 0, sizeof(s));
        t=readStr(s);
        printf("%d\n", trie.prefix(s, t));
    }
    return 0;
}