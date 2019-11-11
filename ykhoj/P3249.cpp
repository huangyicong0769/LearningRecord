#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

struct Node{
    int w, h;
    Node (const int & a, const int& b){
        w=a;
        h=b;
    }
};

stack<Node> s;
int form[1010][1010];

int main(){
    int T;
    for (scanf("%d", &T); T>0; T--){
        int M, N;
        scanf("%d%d", &M, &N);
        for (int i=0; i<M; i++) for (int j=0; j<N; j++) {
            char c[1];
            scanf("%s", c);
            if (c[0]=='F') form[i][j]=((j-1<0)?0:form[i][j-1])+1;
        }
        int ans=0;
        for (int j=0; j<N; j++){
            for (int i=0; i<=M; i++){
                if (s.empty() || s.top().h<form[i][j])
                    s.push(Node(1, form[i][j]));
                else{
                    int w=0;
                    while (!s.empty() && s.top().h>=form[i][j]){
                        w+=s.top().w;
                        ans=max(ans, w*s.top().h);
                        s.pop();
                    }
                    s.push(Node(w+1, form[i][j]));
                }
                form[i][j]=0;
            }
        }
        printf("%d\n", ans*3);
        while(!s.empty()) s.pop();
    }
}
