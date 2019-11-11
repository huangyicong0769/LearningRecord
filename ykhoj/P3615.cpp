#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

int myData[1000][1000], myLeft[1010][1010];

int main(){
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int R, C;
    scanf("%d%d", &R, &C);
    for (int i=0; i<R; i++) for (int j=0; j<C; j++) scanf("%d", &myData[i][j]);
    for (int i=0; i<R; i++) for (int j=0; j<C; j++)
        if (myData[i][j]==myData[i][j-1]) myLeft[i][j]=myLeft[i][j-1]+1;
        else myLeft[i][j]=1;
    for (int i=0; i<C; i++) myLeft[R][i]=0;
    int ans=0;
    for (int j=0; j<C; j++) {
        stack<int> myStack;
        for (int i=0; i<=R; i++){
            #ifdef DEBUG
                printf("%d===\n", i);
            #endif // DEBUG
            if (myStack.size()==0 || myLeft[i][j]>=myStack.top()){
                myStack.push(myLeft[i][j]);
            }else {
                int cnt=0;
                #ifdef DEBUG
                    printf("%d\n :\n", i);
                #endif // DEBUG
                while (myStack.size()>0 && myLeft[i][j]<myStack.top()){
                    #ifdef DEBUG
                        printf();
                    #endif // DEBUG
                    cnt+=myLeft[i][j];
                    myStack.pop();
                }
                #ifdef DEBUG
                    printf("%d\n", cnt);
                #endif //DEBUG
                ans=max(ans, cnt);
            }
        }
    }
    printf("%d\n", ans);
}