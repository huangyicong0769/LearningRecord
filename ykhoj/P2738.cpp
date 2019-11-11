#include <iostream>
#include <cstring>
#define YK 1000000000
using namespace std;

struct Point{
    int x, y;
    bool operator==(const Point& a){
        if (this->x==a.x && this->y==a.y) return 1; else return 0;
    }
}data2738[100100];

int main(){
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
    int T;
    scanf("%d", &T);
    while (T--){
        int N, maxx=-YK-1, maxy=-YK-1, minx=YK+1, miny=YK+1;
        scanf("%d", &N);
        for (int i=0; i<N; i++){
            scanf("%d%d", &data2738[i].x, &data2738[i].y);
            maxx=max(maxx, data2738[i].x);
            maxy=max(maxy, data2738[i].y);
            minx=min(minx, data2738[i].x);
            miny=min(miny, data2738[i].y);
        }
        #ifdef DEBUG
        #endif // DEBUG
        bool bf=1;
        for (int i=0; i<N; i++) 
            if ((data2738[i].x==maxx || data2738[i].x==minx)
            && (data2738[i].y==maxy || data2738[i].y==miny)){
                printf("1\n");
                bf=0;
                break;
            }
        if(bf) printf("2\n");
    }
}