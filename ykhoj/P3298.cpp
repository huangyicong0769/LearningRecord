#include <iostream>
#include <cstdio>
#include <cstring>
#define reg register
#define P 10000

int a[2][2];

inline int read();
void mul(int[2], int[2][2]);
void mulself(int[2][2]);

int main(){
	for (reg int n=read(); n!=-1; n=read()) {
		int f[2]={0, 1},
			a[2][2]={{0, 1}, {1, 1}};
		for (; n; n>>=1){
			if (n&1) mul(f, a);
			mulself(a);
		}
		printf("%d\n", f[0]);
	}
}

inline int read(){
	reg int x=0, f=1; reg char ch=getchar();
	for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
	for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
	return x*f;
}

void mul(int f[2], int a[2][2]){
	int c[2]={0};
	for (reg int i=0; i<2; i++) for (reg int k=0; k<2; k++)
		c[i]=(c[i]+(long long)f[k]*a[k][i])%P;
	memcpy(f, c, sizeof (c));
}

void mulself(int a[2][2]){
	int c[2][2]={0};
	for (reg int i=0; i<2; i++) for (reg int j=0; j<2; j++) for (reg int k=0; k<2; k++)
		c[i][j]=(c[i][j]+(long long)a[i][k]*a[k][j])%P;
	memcpy(a, c, sizeof(c));
}