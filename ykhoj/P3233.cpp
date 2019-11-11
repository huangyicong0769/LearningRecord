#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const int bit=1e9;

int p[100010];
struct BigNum{
    int len;
    BigNum();
    ll x[5000];
    BigNum& operator *=(const int&);
    void out();
};

inline int read();
void add(int, const int&);

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N;  
    N=read();
    for (int i=N+2; i<=N+N; i++) add(i, 1);
    for (int i=1; i<=N; i++) add(i, -1);
    BigNum ans;
    for (int i=1; i<=N+N; i++) while (p[i]) ans*=i, p[i]--;
    ans.out();
}

inline int read(){
    int x=0, f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

BigNum::BigNum(){
    this->len=1;
    this->x[1]=1;
}

BigNum& BigNum::operator *=(const int& b){
    int& l=this->len;
    for (int i=1; i<=l; i++) this->x[i]*=b;
    for (int now=1; now<=l; now++){
        if (this->x[now]>bit) {
            this->x[now+1]+=this->x[now]/bit;
            this->x[now]%=bit;
        }
        if (now==l && this->x[l+1]) l++;
    }
}

void BigNum::out(){
    for (int i=this->len; i>0; i--) if (i==this->len) printf("%lld", this->x[i]); else printf("%09lld", this->x[i]);
    printf("\n");
}

void add(int x, const int& v){
    for (int i=2; i*i<=x; i++)
        while (x%i==0) p[i]+=v, x/=i;
    if (x!=1) p[x]+=v; 
}