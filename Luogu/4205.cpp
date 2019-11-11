#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register int
#define f1(i, s, t) for (reg i = s; i <= t; i++)
#define f2(i, d, s) for (reg i = d[s]; i != s; i = d[i])
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

const int N = 12, SRow = 2756, SCol = 76, SNode = 15100, multag[2] = {1, -1},
          len[12] = {3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5},
          table[12][5][2] =
              {
                  {{0, 0}, {0, 1}, {1, 0}},                    // A
                  {{0, 0}, {0, 1}, {0, 2}, {0, 3}},            // B
                  {{0, 0}, {0, 1}, {1, 0}, {0, 2}},            // C
                  {{0, 0}, {0, 1}, {1, 0}, {1, 1}},            // D
                  {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},    // E
                  {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 1}},    // F
                  {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 2}},    // G
                  {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}},    // H
                  {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}},    // I
                  {{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {0, 2}},  // J
                  {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}},    // K
                  {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}}     // L
},
          numx[56] = {0, 1, 2, 2, 3,  3,  3,  4,  4,  4,  4,  5,  5,  5,
                      5, 5, 6, 6, 6,  6,  6,  6,  7,  7,  7,  7,  7,  7,
                      7, 8, 8, 8, 8,  8,  8,  8,  8,  9,  9,  9,  9,  9,
                      9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
          numy[56] = {0, 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 4, 5, 1, 2, 3,
                      4, 5, 6, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 8, 1,
                      2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int cntRow, cntCol, cnt, u[SNode], d[SNode], r[SNode], l[SNode], row[SNode],
    col[SNode], h[SRow], s[SCol], num[N][N], id[SRow];
bool v[N];
char ch[N][N];

il void init(int C) {
  f1(i, 0, C) {
    r[i] = i + 1;
    l[i] = i - 1;
    u[i] = d[i] = i;
  }
  r[C] = 0, l[0] = C;
  ms(h, -1), ms(s, 0);
  cnt = C + 1;
}
il void link(int R, int C) {
  s[C]++;
  row[cnt] = R, col[cnt] = C;
  u[cnt] = C, d[cnt] = d[C];
  u[d[C]] = cnt, d[C] = cnt;
  if (h[R] == -1)
    h[R] = r[cnt] = l[cnt] = cnt;
  else {
    r[cnt] = h[R], l[cnt] = l[h[R]];
    r[l[h[R]]] = cnt, l[h[R]] = cnt;
  }
  cnt++;
}
il void remove(int C) {
  r[l[C]] = r[C], l[r[C]] = l[C];
  f2(i, d, C) f2(j, r, i) u[d[j]] = u[j], d[u[j]] = d[j], s[col[j]]--;
}
il void resume(int C) {
  f2(i, u, C) f2(j, l, i) u[d[j]] = d[u[j]] = j, s[col[j]]++;
  r[l[C]] = l[r[C]] = C;
}
bool dance() {
  if (r[0] == 0) return 1;
  reg c = r[0];
  f2(i, r, 0) if (s[c] > s[i]) c = i;
  remove(c);
  f2(i, d, c) {
    if (col[i] <= 55) ch[numx[col[i]]][numy[col[i]]] = id[row[i]] + 'A';
    f2(j, r, i) {
      remove(col[j]);
      if (col[j] <= 55) ch[numx[col[j]]][numy[col[j]]] = id[row[j]] + 'A';
    }
    if (dance()) return 1;
    f2(j, l, i) resume(col[j]);
  }
  resume(c);
  return 0;
}

int main() {
  f1(i, 1, 10) scanf("%s", ch[i] + 1);
  f1(i, 1, 10) f1(j, 1, i) if (ch[i][j] != '.') v[ch[i][j] - 'A'] = 1;
  f1(i, 1, 10) f1(j, 1, i) num[i][j] = ++cntCol;
  // f1(i, 1, 10) {f1(j, 1, i) printf("%d ", num[i][j]); puts("");}
  init(cntCol + 12);
  f1(ca, 0, 11) {
    ++cntCol;
    f1(mx, 0, 1) f1(dx, 0, 1) f1(dy, 0, 1) {
      reg p[2];
      for (p[0] = 1; p[0] <= 10; p[0]++)
        for (p[1] = 1; p[1] <= p[0]; p[1]++) {
          register bool flag = 1;
          reg nx[2];
          f1(k, 0, len[ca] - 1) {
            nx[mx] = p[mx] + multag[dx] * table[ca][k][0];
            nx[mx ^ 1] = p[mx ^ 1] + multag[dy] * table[ca][k][1];
            if (v[ca]) {
              if (ch[nx[0]][nx[1]] != ca + 'A') {
                flag = 0;
                break;
              }
            } else if (ch[nx[0]][nx[1]] != '.') {
              flag = 0;
              break;
            }
          }
          if (!flag) continue;
          id[++cntRow] = ca;
          link(cntRow, cntCol);
          f1(k, 0, len[ca] - 1) {
            nx[mx] = p[mx] + multag[dx] * table[ca][k][0];
            nx[mx ^ 1] = p[mx ^ 1] + multag[dy] * table[ca][k][1];
            link(cntRow, num[nx[0]][nx[1]]);
          }
        }
    }
  }
  if (!dance())
    puts("No solution");
  else
    f1(i, 1, 10) printf("%s\n", ch[i] + 1);
}