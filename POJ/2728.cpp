#include <iostream>
#include <cstdio>
#define reg register
#define f(i, s, t) for (reg int i=s; i!=t+1; i++)
using namespace std;

const double exp=1e-6;
const int SIZE=1006;
int N;
double mid;

struct Edge{
  int x, y;
  double c, r;
  bool operator<(const Edge &a) { return c-r*mid>a.c-a.r*mid; }
}edge[SIZE];

int main(){
  while (1){
    scanf("%d", &N);
    if (N==0) continue;
    f()
  }
}
