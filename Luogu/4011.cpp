#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define reg register int
#define il inline
#define f(i, s, t) for (reg i = s; i <= t; i++)

const int SN = 12, d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int N, M, P, K, S, keys[SN][SN], doors[SN][SN][4], gd[3][3];
bool walls[SN][SN][4], in[SN][SN][1 << 10];
struct Node {
  int x, y, st, ti;
};

il int read() {
  reg x = 0; register char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) ;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
  return x;
}

il int bfs() {
  queue<Node> q;
  q.push({1, 1, keys[1][1], 0});
  in[1][1][keys[1][1]] = 1;
  while (q.size()) {
    Node cur = q.front();
    q.pop();
    // printf("%d %d\n", cur.x, cur.y);
    f(i, 0, 3) {
      reg nx = cur.x + d[i][0],  //
          ny = cur.y + d[i][1];
      // printf("  %d %d %d %d %d\n", nx, ny, !in[nx][ny][cur.st | keys[nx][ny]],
      //        !walls[cur.x][cur.y][i],
      //        (doors[cur.x][cur.y][i] & cur.st) == doors[cur.x][cur.y][i]);
      if (nx > 0 && ny > 0 && nx <= N && ny <= M &&
          !in[nx][ny][cur.st | keys[nx][ny]] && !walls[cur.x][cur.y][i] &&
          (doors[cur.x][cur.y][i] & cur.st) == doors[cur.x][cur.y][i]) {
        if (nx == N && ny == M) return cur.ti + 1;
        in[nx][ny][cur.st | keys[nx][ny]] = 1;
        q.push({nx, ny, cur.st | keys[nx][ny], cur.ti + 1});
      }
    }
  }
  return -1;
}

int main() {
  f(i, 0, 3) gd[d[i][0] + 1][d[i][1] + 1] = i;
  N = read(), M = read(), P = read(), K = read();
  f(i, 1, K) {
    reg x1 = read(), y1 = read(), x2 = read(), y2 = read(), g = read(),
        dk = gd[abs(x1 - x2) + 1][abs(y1 - y2) + 1];
    if (g == 0)
      walls[x1][y1][dk] = walls[x2][y2][dk ^ 1] = 1;
    else {
      doors[x1][y1][dk] |= 1 << (g - 1);
      doors[x2][y2][dk ^ 1] |= 1 << (g - 1);
    }
  }
  S = read();
  f(i, 1, S) {
    reg x = read(), y = read(), q = read();
    keys[x][y] |= 1 << (q - 1);
  }
  printf("%d\n", bfs());
}