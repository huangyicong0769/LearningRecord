#include <stdio.h>

const char ERROR[] = "Uh-oh",
           OVER[] = "Game Over",
           FINISH[] = "Congratulations!";

int input(char* s){
    printf("%s", s);
    int x;
    scanf("%d", &x);
    return x;
}

void inputCharArr2(char* s, int n, int m, int* a, int Col){
    printf("%s", s);
    for (register int i = 0; i < n; i++)
        for (register int j = 0; j < m; j++){
            register char ch = getchar();
            while (ch == ' ' || ch == '\n') ch = getchar();
            *(a + i*Col + j) = ch;
        }
}

void inputIntArr2(char* s, int n, int m, int* a, int Col){
    printf("%s", s);
    for (register int i = 0; i < n; i++)
        for (register int j = 0; j < m; j++)
            scanf("%d", a + i*Col + j);
}

int isAllStar(int n, int m, int* a, int Col){
    for (register int i = 0; i < n; i++)
        for (register int j = 0; j < m; j++)
            if (*(a + i*Col + j) != '*') return 0;
    return 1;
}

void outputCharArr2(int n, int m, int* a, int Col){
    for (register int i = 0; i < n; i++){
        for (register int j = 0; j < m; j++)
            printf("%c ", *(a + i*Col + j));
        printf("\n");
    }
}

int main(){
    int n = input("Enter n:");
    int ch[13][13];
    inputCharArr2("Enter an array:\n", 2*n, 2*n, ch, 13);
    // outputCharArr2(2*n, 2*n, ch, 13);
    int m = input("Enter m:");
    int query[m][4];
    inputIntArr2("Enter an array:\n", m, 4, query, 4);
    int cntErr = 0;
    for (register int i = 0; i < m; i++){
        if (ch[query[i][0] - 1][query[i][1] - 1] != '*' &&
            ch[query[i][0] - 1][query[i][1] - 1] == ch[query[i][2] - 1][query[i][3] - 1]){
            ch[query[i][0] - 1][query[i][1] - 1] = '*';
            ch[query[i][2] - 1][query[i][3] - 1] = '*';
            outputCharArr2(2*n, 2*n, ch, 13);
        }else{
            puts(ERROR);
            if (++cntErr == 3){
                puts(OVER);
                break;
            } 
        }
        if (isAllStar(2*n, 2*n, ch, 13)){
            puts(FINISH);
            break;
        }
    }
}