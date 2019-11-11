#include <iostream>
#include <cstdio>
#include <cstring>
#define N 16
using namespace std;

typedef unsigned short us;

char ch[16][16];
us suit[16][16];
int ct;
bool done;

inline void update(const int &, const int &, const int &);
inline int cont(const us &); //count 1
inline void oganization();
void dfs(int, int);

int main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    while (1){
        memset(ch, 0, sizeof(ch)); 
        memset(suit, 0, sizeof(suit));
        for (register int i = 0; i < N; i++) for (register int j = 0; j < N; j++)
            for (ch[i][j] = getchar(); (ch[i][j] < 'A' || ch[i][j] > 'Z') && ch[i][j] != '-'; ch[i][j] = getchar()) if (ch[i][j] == EOF) return 0;
        done = 0;
        oganization();
        dfs(-1, -1);
        puts("");
    }
}

void dfs(int x, int y){
    if (done) return;
    us o[16][16];
    char oc[16][16];
    memcpy(oc, ch, sizeof(ch));
    memcpy(o, suit, sizeof(suit));
    oganization();
    for (register int i = 0; i < N; i++) for (register int j = 0; j < N; j++) if (ch[i][j] == '-') {
        if (suit[i][j] == 0xFFFF){
            memcpy(ch, oc, sizeof(ch));
            memcpy(suit, o, sizeof(suit));
            return;
        }
        if (cont(suit[i][j]) == 15) {
            suit[i][j] = 0xFFFF;
            ch[i][j] = 'A' + ct;
            update(i, j, ct);
        }
    }
    for (register int i = 0; i < N; i++) for (register char tch = 0; tch < N; tch++) {
        int cnt = 0, k = -1;
        for (register int j = 0; j < N; j++)
            if (ch[i][j] == tch + 'A') cnt = 0xFFFF;
            else if (((suit[i][j] >> tch) & 1) == 0){
                cnt++;
                k = j;
            }
        if (cnt == 0){
            memcpy(ch, oc, sizeof(ch));
            memcpy(suit, o, sizeof(suit));
            return;
        }
        if (cnt == 1){
            suit[i][k] = 0xFFFF;
            ch[i][k] = tch + 'A';
            update(i, k, tch);
        }
    }
    for (register int j = 0; j < N; j++) for (register char tch = 0; tch < N; tch++) {
        int cnt = 0, k = -1;
        for (register int i = 0; i < N; i++)
            if (ch[i][j] == tch + 'A') cnt = 0xFFFF;
            else if (((suit[i][j] >> tch) & 1) == 0){
                cnt++;
                k = i;
            }
        if (cnt == 0) {
            memcpy(ch, oc, sizeof(ch));
            memcpy(suit, o, sizeof(suit));
            return;
        }
        if (cnt == 1){
            suit[k][j] = 0xFFFF;
            ch[k][j] = tch + 'A';
            update(k, j, tch);
        }
    }
    for (register int x = 0; x < 4; x++) for (register int y = 0; y < 4; y++) for (register char tch = 0; tch < N; tch++){
        int cnt = 0, k1 = -1, k2 = -1;
        for (register int i = x * 4; i < x * 4 + 4; i++) for (register int j = y * 4; j < y * 4 + 4; j++)
            if (ch[i][j] == tch + 'A') cnt = 0xFFFF;
            else if (((suit[i][j] >> tch) & 1) == 0){
                cnt++;
                k1 = i;
                k2 = j;
            }
        if (cnt == 0){
            memcpy(ch, oc, sizeof(ch));
            memcpy(suit, o, sizeof(suit));
            return;
        }
        if (cnt == 1){
            suit[k1][k2] = 0xFFFF;
            ch[k1][k2] = tch + 'A';
            update(k1, k2, tch);
        }
    }
    int tmax = -1, k1 = -1, k2 = -1;
    for (register int i = 0; i < N; i++) for (register int j = 0; j < N; j++) if (ch[i][j] == '-'){
        int t = cont(suit[i][j]);
        if (t > tmax){
            tmax = t;
            k1 = i;
            k2 = j;
        }
    }
    if (k1 == -1 && k2 == -1){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++) printf("%c", ch[i][j]);
            printf("\n");
        }
        done = 1;
        return;
    }
    for (register us t = suit[k1][k2], cnt = 0; cnt<N && !done; cnt++, t >>= 1) if ((t & 1)==0){
        suit[k1][k2] |= 1 << cnt;
        ch[k1][k2] = cnt + 'A';
        dfs(k1, k2);
        suit[k1][k2] ^= 1 << cnt;
        ch[k1][k2] = '-';
    }
    memcpy(ch, oc, sizeof(ch));
    memcpy(suit, o, sizeof(o));
}

inline void oganization(){
    for (register int i = 0; i < N; i++) for (register int j = 0; j < N; j++) if (ch[i][j] != '-'){
        suit[i][j] = 0xFFFF;
        update(i, j, ch[i][j]-'A');
    }
}

inline void update(const int &x, const int &y, const int &ch){
    for (register int t = 0; t < N; t++){
        if (y != t) suit[x][t] |= 1 << ch;
        if (x != t) suit[t][y] |= 1 << ch;
    }
    for (register int ti = x / 4 * 4; ti < x / 4 * 4 + 4; ti++) for (register int tj = y / 4 * 4; tj < y / 4 * 4 + 4; tj++) if (ti != x && tj != y) suit[ti][tj] |= 1 << ch;
}

inline int cont(const us &a){
    int ans = 0; ct=-1;
    for (us t = a, cnt = 0; t; t >>= 1, cnt++){
        if (t & 1) ans++;
        if (!(t & 1)) ct = cnt;
    }
    if (ct==-1) ct=15;
    return ans;
}