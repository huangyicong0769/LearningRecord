#include <stdio.h>

const int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int a[13][13];

int input(char* s){
    printf("%s", s);
    int x;
    scanf("%d", &x);
    return x;
}

int main(){
    int n = input("Enter n:");
    for (register int i = 1, x = 0, y = 0, k = 0; i <= n*n; i++){
        a[x][y] = i;
        if (i == n*n) break;
        int tx = x + direction[k][0],
            ty = y + direction[k][1];
        if (tx >= 0 && tx < n && ty >=0 && ty < n && a[tx][ty] == 0){
            x = tx;
            y = ty;
        }else {
            k = (k + 1)%4;
            i--;
        }
    }
    for (register int i = 0; i < n; i++){
        for (register int j = 0; j < n; j++)
            printf("%3.d", a[i][j]);
        printf("\n");
    }
}