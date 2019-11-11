#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const int P=99991;
int snow[100100][6];
vector<int> hash1[100100];

int encode(int);
bool equal(int*, int*);
bool insert(int);

int main(){
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif //LOCAL
	int N;
	while (scanf("%d", &N)!=EOF){
		for (int i=0; i<P; i++) hash1[i].clear();
		bool b=1;
		for (int i=0; i<N; i++){
			for (int j=0; j<6; j++) scanf("%d", &snow[i][j]);
			if (b && insert(i)) {
				puts("Twin snowflakes found.");
				b=0;
			}
		}
		if (b) puts("No two snowflakes are alike.");
	}
}

int encode(int a){
	ll cnt1=0, cnt2=1;
	for (int i=0; i<6; i++){
		(cnt1+=snow[a][i])%=P;
		(cnt2*=(ll)snow[a][i])%=P;
	}
	return (cnt1+cnt2)%P;
}

bool equal(int* a, int* b){
	for (int s1=0; s1<6; s1++) 
	for (int s2=0; s2<6; s2++){
		bool eq=1;
		for (int i=0; i<6; i++) if (a[(s1+i)%6]!=b[(s2+i)%6]) eq=0;
		if (eq) return 1;
		eq=1;
		for (int i=0; i<6; i++) if (a[(s1+i)%6]!=b[(s2-i+6)%6]) eq=0;
		if (eq) return 1;
	}
	return 0;
}

bool insert(int a){
	int val=encode(a);
	for (int i=0; i<hash1[val].size(); i++)
		if (equal(snow[hash1[val][i]], snow[a])) return 1;
	hash1[val].push_back(a);
	return 0;
}
