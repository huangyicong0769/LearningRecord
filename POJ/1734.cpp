#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define mc(a, b) memcpy(a, b, sizeof(b))
using namespace std;

typedef long long ll;

const int SIZE = 106, INF = 0x3f3f3f3f;
int N, M, a[SIZE][SIZE], d[SIZE][SIZE], pos[SIZE][SIZE];
vector<int> path;

void getPath(int x, int y) {
  if (pos[x][y] == 0) return;
  getPath(x, pos[x][y]);
  path.push_back(pos[x][y]);
  getPath(pos[x][y], y);
}

int main() {
  scanf("%d%d", &N, &M);
  ms(a, 0x3f);
  f(i, 1, N) a[i][i] = 0;
  f(i, 1, M) {
    reg A, B, T;
    scanf("%d%d%d", &A, &B, &T);
    a[A][B] = a[B][A] = min(T, a[A][B]);
  }
  mc(d, a);
  reg ans = INF;
  f(k, 1, N) {
    f(i, 1, k - 1)
        f(j, i + 1, k - 1) if ((ll)d[i][j] + a[j][k] + a[k][i] < ans) {
      ans = d[i][j] + a[j][k] + a[k][i];
      path.clear();
      path.push_back(i);
      getPath(i, j);
      path.push_back(j);
      path.push_back(k);
    }
    f(i, 1, N) f(j, 1, N) if (d[i][j] > d[i][k] + d[k][j]) {
      d[i][j] = d[i][k] + d[k][j];
      pos[i][j] = k;
    }
  }
  if (ans == INF)
    puts("No solution.");
  else {
    f(i, 0, (int)path.size() - 1) printf("%d ", path[i]);
    puts("");
  }
}