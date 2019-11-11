#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

struct Node{
    int children[10];
    bool pN, haveChild;
}ORIGIN;

vector<Node> Trie;

inline int read();

int main(){
    for (int T=read(); T; T--){
        Trie.clear();
        Trie.push_back(ORIGIN);
        const int N=read();
        bool arch=0;
        for (int i=0; i<N; i++){
            int last=0;
            char ch=getchar();
            for (; ch<'0' || ch>'9'; ch=getchar());
            for (; ch>='0' && ch<='9'; ch=getchar()){
                if (Trie[last].children[ch-'0']==0){
                    Trie[last].children[ch-'0']=Trie.size();
                    Trie[last].haveChild=1;
                    Trie.push_back(ORIGIN);
                }
                last=Trie[last].children[ch-'0'];
                if (Trie[last].pN) arch=1;
            }
            Trie[last].pN=1;
            if (Trie[last].haveChild) arch=1;
        }
        if (arch) printf("NO\n"); else printf("YES\n");
    }
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