#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int T;
    scanf("%d", &T);
    while (T--){
        double H, h, D;
        scanf("%lf%lf%lf", &H, &h, &D);
        double x=sqrt((H-h)*D);
        if (x>=D-h*D/H && x<=D) printf("%.3lf\n", D+H-2*x);
        else if (x>D) printf("%.3lf\n", h);
        else printf("%.3lf\n", h*D/H);  
    }
}