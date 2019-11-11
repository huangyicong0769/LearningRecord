#include <iostream>
#include <cstdio>
#include <queue>
#include <map>
#define reg register
using namespace std;

const int N=33331;

struct Node{
    int x, y, s, e;
    bool operator<(const Node &)const;
}now;

priority_queue<Node> pq;
vector<int> v1[N], v2[N];

int P;

bool myHash(const int &, const int &);
int gcd(int, int);
inline int evluate(const int &);
inline bool insert(int, int);
inline int bfs();

int main(){
    scanf("%d", &P);
    printf("%d\n", bfs());
    return 0;
}

bool Node::operator<(const Node & that)const{
    return this->s+this->e > that.s+ that.e || 
        this->s+this->e == that.s+ that.e && this->s > that.s;
}

bool myHash(const int & a, const int & b){
    int x=a%N, j=-1;
    bool find=0;
    for (reg int i=0; i<v1[x].size(); i++) if (v1[x][i]==a) {
        find=1;
        j=i;
        break;
    }
    if (find && v2[x][j]<=b) return false;
    if (find) v2[x][j]=b;
    else v1[x].push_back(a), v2[x].push_back(b);
    return true;
}

int gcd(int x, int y){
    if (x%y==0) return y;
    else return gcd(y, x%y);
}

inline int evluate(const int & a){
    int ans=0;
    for (reg int b=a; b<P; ans++, b*=2);
    return ans;
}

inline bool insert(int x, int y){
    if (y>x) swap(x, y);
//    printf("%d %d\n", x, y);
    if (x>2*P) return false;
//    printf("!1\n");
    if (x>P && y==0) return false;
//    printf("!2\n");
    if (x==y) return false;
//    printf("!3\n");
    if (y!=0 && P%gcd(x, y)) return false;
//    printf("!4\n");
    if (!myHash(x*40000+y, now.s+1)) return false;
//    printf("!5\n");
    pq.push((Node){x, y, now.s+1, evluate(x)});
    return true;
}

inline int bfs(){
    pq.push((Node){1, 0, 0, evluate(1)});
    myHash(1*40000, 0);
    while (pq.size()){
        now=pq.top(); pq.pop();
        const int & x=now.x, y=now.y;
        if (x==P || y==P) return now.s;
        insert(x+x, y);
        insert(x-y, y);
        insert(x+y, y);
        insert(y+y, y);
        insert(x, x+y);
        insert(x, y+y);
        insert(x, x+x);
    }
    return -1;
}