#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define reg register
#define N 24
using namespace std;

const int d[4][7]={{0, 2, 6, 11, 15, 20, 22},
				   {1, 3, 8, 12, 17, 21, 23},
				   {4, 5, 6, 7, 8, 9, 10},
				   {13, 14, 15, 16, 17, 18, 19}},
		  e[8]={6, 7, 8, 11, 12, 15, 16, 17},
		  m[8]={0, 0, 1, 1, 1, 1, 0, 0},
		  u[8]={5, 4, 7, 6, 1, 0, 3, 2};
const char c[8]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

vector<int> v;

int M, ans2;

short a[24];

inline void _debug(){
	for (reg int i=0; i<N; i++) printf("%d ", a[i]); printf("\n");
}
inline int read();
inline int evluate();
inline void deal(const int&);
bool dfs(int, int);

int main(){
//	freopen("output.txt", "w", stdout);
	for (;;){
		for (reg int i=0; i<N; i++) {
			a[i]=read();
			if (a[i]==0) return 0;
		}
		v.clear();
		if (evluate()==0) puts("No moves needed");
		else {
			for (M=evluate(); !dfs(0, -1); M++);
			for (reg int i=v.size()-1; i>=0; i--) printf("%c", c[v[i]]);
			printf("\n%d\n", ans2);
		}
	}
}

inline int read(){
	reg int x=0; reg char ch=getchar();
	for (; ch<'0' || ch>'9'; ch=getchar()) if (ch==EOF) return EOF;
	for (; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
	return x;
}

inline int evluate(){
	int ans=9, cnt[4]={0};
	for (reg int j=0; j<8; j++) cnt[a[e[j]]]++;
	for (reg int i=1; i<4; i++) ans=min(ans, 8-cnt[i]);
	return ans;
}

inline void deal(const int & id){
//	printf("?\n");
    int tid=id>=4?u[id]:id;
	if (m[id]==1){
		int t=a[d[tid][6]];
//		_debug();
		for (reg int k=6; k>0; k--) a[d[tid][k]]=a[d[tid][k-1]];
//		_debug();
		a[d[tid][0]]=t;
//		_debug();
	}else{
		int t=a[d[tid][0]];
		for (reg int k=0; k<6; k++) a[d[tid][k]]=a[d[tid][k+1]];
		a[d[tid%4][6]]=t;
	}
//	printf("!\n");
}

bool dfs(int step, int la){
//	 cout<<moves<<' '<<la<<' '<<evluate()<<endl;
//     _debug();
	if (evluate()==0) {
		ans2=a[e[0]];
		return true;
	}
	if (step+evluate()>M) return false;
	for (reg int k=0; k<8; k++)if (la==-1 || k!=u[la]){
		deal(k);
		if (dfs(step+1, k)) {
			v.push_back(k);
			return true;
		}
		deal(u[k]);
	}
	return false;
}