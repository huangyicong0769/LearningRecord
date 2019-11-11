#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

vector<int> a, b, f, g;

int main(){
    //freopen("input.txt", "r", stdin);
	int n;
	while (scanf("%d", &n)!=EOF){
        //cout<<"===\n";
        a.clear(), b.clear(), f.clear(), g.clear();
		for (int i=1; i<=trunc(sqrt(n)); i++)if (n%i==0){
			if (n/i!=i) a.push_back(i), b.push_back(n/i);
			else a.push_back(i);
		}
		for (int i=b.size()-1; i>=0; i--) a.push_back(b[i]);
        //for (int i=0; i<a.size(); i++) printf("%d ", a[i]); printf("\n");
        f.push_back(0), g.push_back(1);
        for (int i=1; i<a.size(); i++) {
            f.push_back(1);
            g.push_back(1);
            for (int j=1; j<i; j++)if (a[i]%a[j]==0){
                //printf("%d %d\n", i, j);
                if (f[i]<f[j]+1) {
                    g[i]=g[j];
                    f[i]=f[j]+1;
                }else if (f[i]==f[j]+1){
                    g[i]+=g[j];
                }
            }
        }
        printf("%d %d\n", f[f.size()-1], g[g.size()-1]);
	}
}