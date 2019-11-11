#include <iostream>
#include <cstdio>
#include <cmath>
#define il inline
#define reg register
#define f1(a, b, c) for (reg int a=b; a<=c; a++)
#define f2(a, b, c) for (reg int a=b; a>=c; a--)
#define lowbit(x) x&-x
#define MAXN 8010
using namespace std;

const int pow2[14]={1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

int N, a[MAXN], c[MAXN], h[MAXN];

il void init();
il int ask(const int &);
il void edit(int, const int &);
il int read();

int main(){
	f2 (i, N=read(), 2) a[N-i+2]=read();
    init();
	// for (int i=1; i<=N; i++) printf("%d ", a[i]); printf("\n");
	f2 (i, N, 1) edit(h[i]=ask(a[i]), -1);
	f1 (i, 1, N) printf("%d\n", h[i]);
}

il void init(){	
	f1 (i, 1, N) edit(i, 1);
	f1 (i, 1, N) a[i]++;
}

il int ask(const int & x){
	int ans=0, sum=0;
	f2 (p, (int)log2(N), 0) 
		if(ans+pow2[p]<=N && sum+c[ans+pow2[p]]<x) {
			ans+=pow2[p];
			sum+=c[ans];
		} 
	return ans+1;
}

il void edit(int x, const int & y){
	for (; x<=N; x+=lowbit(x)) c[x]+=y;
}

il int read(){
	reg int x=0; reg char ch=getchar();
	for (; ch<'0' || ch>'9'; ch=getchar());
	for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
	return x;
}
