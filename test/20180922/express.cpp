#include <iostream>
#include <cstdio>
using namespace std;

int X[200100], Y[200100], S[200100];

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++) scanf("%d%d%d", &X[i], &Y[i], &S[i]);
    double f=(double)S[0]/X[0];
    double g=(double)S[0]/Y[0];
    for (int i=1; i<N; i++){
        if (Y[i-1]>=X[i]) f=max(f, (double)(S[i]/(X[i]-X[i-1])));
        else f=max(f, min((double)(S[i]/(X[i]-X[i-1])), (double)(S[i]/(X[i]-Y[i-1]))));
        if (Y[i-1]>=Y[i]) g=max(g, (double)(S[i]/(Y[i]-X[i-1])));
        else g=max(g, min((double)(S[i]/(Y[i]-X[i-1])), (double)(S[i]/(Y[i]-Y[i-1]))));
    }
    printf("%.2lf\n", min(f, g));
}