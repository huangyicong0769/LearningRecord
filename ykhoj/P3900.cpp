#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int cnt[1000100];
vector<int> v1;

int main(){
    //freopen("input.txt", "r", stdin);
    for (int i=2; i<1000010; i++){
        if (cnt[i]==0){
            v1.push_back(i);
            cnt[i]=i;
        }
        for (int j=0; j<v1.size(); j++){
            if (v1[j]>cnt[i] || v1[j]>1000010/i) break;
            cnt[i*v1[j]]=v1[j];
        }
    }
    while (1){
        int N;
        scanf("%d", &N);
        if (N==0) break;
        for (int i=0; i<v1.size(); i++) {
            if (v1[i]>N) {
                printf("Goldbach's conjecture is wrong.\n");
                break;
            }
            if (cnt[N-v1[i]]==N-v1[i]){
                printf("%d = %d + %d\n", N, v1[i], N-v1[i]);
                break;
            }
        }
    }
}