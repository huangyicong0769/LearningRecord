#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <cmath>
#define N 9
#define CH
using namespace std;

const int di[4]={-1, 1, -3, 3};
const char ci[4]={'l', 'r', 'u', 'd'};

struct Node{
    string state, move;
    int v, xs;
    bool operator<(const Node&)const;
};

int dms[10];

bool is[416100];

string O;

int mergeSort(int, int);
inline bool able();
inline int evaluate(const string &);
inline bool repeat(const string &);
#ifdef CH
inline string bfs();
#else
inline int bfs();
#endif

int main(){
    for (register int i=0; i<N; i++) {
        char c;
        cin>>c;
        O+=c;
    }
    if (able()) puts("unsolvable");
    else cout<<bfs()<<endl;
}

bool Node::operator<(const Node & a)const{
    return this->v > a.v;
}

int mergeSort(int x, int y){
    cout<<x<<' '<<y<<endl;
    if (x>=y) return 0;
    int mid=(x+y)>>1, tmp[10], ans=0;
    if (y-x>1) ans+=mergeSort(x, mid), ans+=mergeSort(mid+1, y);
    register int l=x, r=mid+1, t=0;
    for (;l<=mid && r<=y; cout<<" "<<l<<' '<<r<<endl)
        if (dms[l]<dms[r]) tmp[t++]=dms[l++];
        else {
        	tmp[t++]=dms[r++]; ans+=mid-l+1;
        }
    for (;l<=mid; l++) tmp[t++]=dms[l];
    for (;r<=y; r++) tmp[t++]=dms[r];
    for (register int i=x, j=0; i<=y, j<t; i++, j++) dms[i]=tmp[j];
    return ans;
}

inline bool able(){
    for (register int i=0; i<N; i++) if (O[i]=='x') dms[i]=9; else dms[i]=O[i]-'0';
    int cnt=mergeSort(0, N-1);
    for (register int i=0; i<N; i++) printf("%d ", dms[i]); printf("\n%d\n", cnt);
    return cnt%2;
}

inline int evaluate(const string & s){
    int ans=0;
    for (register int i=0; i<N; i++){

    }
    return ans;
}

inline bool repeat(const string & s){
    int t=0;
    for (register int i=0, j=40320, k=N-1; i<N; i++, j/=(k==0?j:k), k--)
        if (s[i]=='x') t+=9*j;
        else t+=9*j;
    if (is[t]) return true;
    is[t]=1;
    return false;
}

#ifdef CH
inline string bfs(){
#else 
inline int bfs(){
#endif
    int t;
    for (register int i=0; i<N; i++) if (O[i]=='x') t=i;
    priority_queue<Node> pq;
    pq.push((Node){O, "", evaluate(O), t});
    repeat(O);
    while (pq.size()){
        Node now=pq.top(); pq.pop();
        cout<<now.move<<endl;
        if (now.state=="12345678x") {
#ifdef CH
            return now.move;
#else
            return now.v;
#endif // CH
        }
        for (register int k=0; k<4; k++){
            int nxs=now.xs+di[k];
            if (nxs>=0 && nxs<9 && (k<2 && (nxs-1)/3==(now.xs-1)/3) || k>=2){
                Node t=now; t.xs=nxs;
                swap(t.state[now.xs], t.state[nxs]);
                if (repeat(t.state)) continue;
                t.move+=ci[k];
                t.v++;
                pq.push(t);
            }
        }
    }
}
