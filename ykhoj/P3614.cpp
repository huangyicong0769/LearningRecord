#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, f[5][100000], t[100000];
bool is[100000];
vector<int> vMap[100000];

void dpT(int);

bool myComp(const int&, const int&);

int main(){
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
    #endif // DEBUG
	scanf("%d", &N);
	for (int i=1; i<N; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		vMap[a].push_back(b);
		vMap[b].push_back(a);
	}
    is[0]=1;
	dpT(0);
	printf("%d\n", max(max(f[0][0], f[1][0]), f[3][0]));
}

bool myComp(const int& a, const int& b){
    return a>b;
}

void dpT(int x){
	int cnt=0, cntt=0, tot=0;
	for (int i=0; i<vMap[x].size(); i++){
		int j=vMap[x][i];	
        if (is[j]) continue;
        tot++;
        is[j]=1;
		dpT(j);
		cnt+=f[0][j];
		cntt=max(cntt, f[2][j]-f[0][j]);
		f[0][x]+=max(f[0][j], max(f[1][j], f[3][j]));
		t[i]=f[4][j]-f[0][j];
	}
	sort(t, t+tot, myComp);
	if (tot>=3) f[1][x]=cnt+t[0]+t[1]+t[2]+1;
	if (tot>=2) f[2][x]=cnt+t[0]+t[1]+1;
	f[3][x]=cnt+cntt;
	f[4][x]=cnt;
    #ifdef DEBUG
        printf("%d %d %d ", x, vMap[x].size(), tot);
        for (int i=0; i<5; i++) printf("%d ", f[i][x]); 
        for (int i=0; i<tot; i++) printf("%d ", t[i]);
        printf("\n");
    #endif // DEBUG
}