#include <iostream>
#include <cstdio>
using namespace std;

int N, K, fa[100000], f[100000];



int main(){
    scanf("%d%d", &N, &K);
    for (int i=1; i<N; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        fa[b]=a;
    }
}