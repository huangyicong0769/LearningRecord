#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int power=8;
const ll base=1e8;
const int maxn=1507;
void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');//快速输出
}
struct Bignum//压位高精模板
{
    ll v[maxn];
    Bignum() {
        memset(v,0,sizeof v);
    }
    Bignum(string s){//将string 转 Bignum
        memset(v,0,sizeof v);
        int len=s.length();
        v[0]=(len+power-1) / power;
        for(int i=0,t=0,w=0;i<len;w*=10,++i){
            if(i%power == 0)    w=1,++t;
            v[t]+=w*(s[i]-'0');
        }
    }
    void print(){//打印，如果一次不足power位补0
        write(v[v[0]]);
        for(int i=v[0]-1;i>0;--i){
            for(int k=base/10;v[i]<k;k/=10) putchar('0');
            if(v[i]) write(v[i]); 
        }
        printf("\n");  
    }
}p,q,ans,tmp;

int operator <(const Bignum &p,const Bignum &q){//重载 < 
    if(p.v[0] < q.v[0]) return 1;
    if(p.v[0] > q.v[0]) return 0;
    for(int i=p.v[0];i>0;--i)
        if(p.v[i] != q.v[i]) return p.v[i] < q.v[i];
    return 0;
}

Bignum operator - (const Bignum &p,const Bignum &q){//重载 -
    Bignum c=p;
    fors(i,1,c.v[0]){
        c.v[i]-=q.v[i];
        if(c.v[i] < 0){
            c.v[i]+=base;
            --c.v[i+1];
        }
    }
    while(c.v[0] > 0 && !c.v[c.v[0]]) --c.v[0];
    return c;
}

Bignum zero=Bignum("0");
Bignum one=Bignum("1");
void chu(Bignum &a){//模拟 /2
    int i;
    for(i=a.v[0];i>1;i--){
        a.v[i-1]+=(a.v[i]&1)*base;
        a.v[i]>>=1;
    }
    a.v[1]>>=1;
    while(!a.v[a.v[0]]&&a.v[0]>0) a.v[0]--;
}
void cheng(Bignum &a){//模拟 *2
    int i;
    for(i=1;i<=a.v[0];++i)a.v[i]<<=1;
    for(i=1;i<=a.v[0]+1;++i){
        a.v[i+1]+=a.v[i]/base;
        a.v[i]%=base;
    }
    while(a.v[a.v[0]+1]&&a.v[0]<=maxn)a.v[0]++;
}
Bignum gcd(Bignum &a,Bignum &b){//Stein算法的非递归版本
    int tmps=0;
    while(1){
        if(a<one) break;//等同于 if(a==0)
        if(a.v[1]&0 && b.v[1]&0){//a.v[1]相当于末尾的几位数
            ++tmps;chu(a),chu(b);//tmps 累计多少个因子 ：2
            continue;
        }
        if(a.v[1]&0) {
            chu(a);
            continue;
        }
        if(b.v[1]&0) {
            chu(b);
            continue;
        }
        tmp=a;
        (a<b) ? a=b-a : a=a-b;
        b=tmp<b ? tmp:b;
    }
    fors(i,1,tmps)//累乘 2
        cheng(b);
    return b;
}
string str1,str2;
int main(int argc, char const *argv[])
{
    cin>>str1>>str2;
    reverse(str1.begin(),str1.end());//字符串反转
    reverse(str2.begin(),str2.end());
    p=Bignum(str1),q=Bignum(str2);//转换
    ans=gcd(p,q);
    ans.print();
    return 0;

}