#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int N, a[100], cnt, len;
bool b[100];

bool dfs(int, int, int);

int main(){
	for  (scanf("%d", &N); N!=0; scanf("%d", &N)) {
	int sum=0, mV=0;
	for (int i=0; i<N; i++){
		scanf("%d", &a[i]);
		sum+=a[i];
		mV=max(mV, a[i]);
	}
	sort(a, a+N);
	reverse(a, a+N);
	for (len=mV; len<=sum; len++){
		if (sum%len) continue;
		cnt=sum/len;
		memset(b, 0, sizeof(b));
		if (dfs(1, 0, 0)) {
			printf("%d\n", len);
			break;
		}
	}
    }
}

bool dfs(int num, int now, int last){
	if (num>cnt) return true;
	if (now==len) return dfs(num+1, 0, 0);
	int fail=0;
	for (int i=last; i<N; i++){
		if (!b[i] && now+a[i]<=len && fail!=a[i]){
			b[i]=1;
			if (dfs(num, now+a[i], i+1)) return true;
			b[i]=0;
			fail=a[i];
			if (now==0) return false;
		}
	}
	return false;
}