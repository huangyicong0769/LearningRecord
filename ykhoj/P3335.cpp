#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
using namespace std;

struct Node{
    int val, pos;
    Node(const int& a, const int& b){
        this->val=a;
        this->pos=b;
    }
    bool operator<(const Node& a)const{
        return this->val<a.val || this->val==a.val && this->pos<a.pos;
    }
};

set<Node> s;

inline int read();

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N=read();
    for (int i=0; i<N; i++){
        Node a(read(), i+1);
        s.insert(a);
        if (i>0){
            set<Node>::iterator i=s.find(a);
            int k=-1, cnt=-1;
            if (i!=s.begin()) {
                i--;
                k=i->pos, cnt=abs(i->val-a.val);
                i++;
            }
            i++;
            if (s.find(a)==s.begin() || i!=s.end() && abs(i->val-a.val)<cnt) {
                k=i->pos;
                cnt=abs(i->val-a.val);
            }
            printf("%d %d\n", cnt, k);
        }
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
