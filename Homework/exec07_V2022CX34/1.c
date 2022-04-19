#include <stdio.h>

int main(){
    double height, dist = 0;
    int n;
    printf("Enter height: "); scanf("%lf", &height);
    printf("Enter n: "); scanf("%d", &n);
    for (register int i = 0; i < n; i++){
        dist += height;
        height /= 2;
        dist += height;
    }
    dist -= height;
    printf("distance = %.1lf\nheight = %.1lf\n", dist, height);
    return 0;
}