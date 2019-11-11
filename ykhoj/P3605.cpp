#include <iostream>
#include <cstdio>
using namespace std;

struct Node{
    int x, v;
}data[300000];
int N;

int main(){
    scanf("%d", &N);
    for (int i=0; i<N; i++) scanf("%d%d", &data[i].x, &data[i].v);
}