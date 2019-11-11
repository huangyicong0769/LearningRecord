#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;

struct Node{
    int time, level;
}mach[100100], task[100100];

int capacity[130];

bool myComp(const Node& a, const Node& b){
    return a.time>b.time || a.time==b.time && a.level>b.level;
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int N, M;
    while (scanf("%d%d", &N, &M)!=EOF){
        memset(capacity, 0, sizeof(capacity));
        for (int i=0; i<N; i++) scanf("%d%d", &mach[i].time, &mach[i].level);
        for (int i=0; i<M; i++) scanf("%d%d", &task[i].time, &task[i].level);
        sort(mach, mach+N, myComp);
        sort(task, task+M, myComp);
        ll ans1=0, ans2=0;
        for (int i=0, j=0; i<M; i++){
            while (mach[j].time>=task[i].time && j<N){
                capacity[mach[j].level]++;
                j++;
            }
            int k=j;
            for (int k=task[i].level; k<101; k++) if (capacity[k]) {
                capacity[k]--;
                ans1++;
                ans2+=500*task[i].time+2*task[i].level;
                break;
            }
        }
        printf("%lld %lld\n", ans1, ans2);
    }
}