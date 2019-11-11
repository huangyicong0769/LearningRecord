#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int fen[100] = {0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7,
                8, 8, 8, 8, 8, 7, 6, 6, 7, 8, 9, 9, 9, 8, 7, 6, 6, 7, 8, 9, 10,
                9, 8, 7, 6, 6, 7, 8, 9, 9, 9, 8, 7, 6, 6, 7, 8, 8, 8, 8, 8, 7,
                6, 6, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
const int N = 9;
const int mm = N * N * N * N * N * 4 + N;
const int mn = N * N * N + N;
int map[10][10];
int ans = -1, size;
int U[mm], D[mm], L[mm], R[mm], C[mm], X[mm];
int S[mn], Q[mn], H[mn];
bool v[mn];
inline void prepare(int r, int c) {
  for (int i = 0; i <= c; ++i) {
    S[i] = 0;
    U[i] = D[i] = i;
    L[i + 1] = i;
    R[i] = i + 1;
  }
  R[size = c] = 0;
  while (r) H[r--] = -1;
}
inline void place(int &r, int &c1, int &c2, int &c3, int &c4, int i, int j,
                  int k) {
  r = ((i - 1) * N + j - 1) * N + k;
  c1 = (i - 1) * N + j;
  c2 = N * N + (i - 1) * N + k;
  c3 = N * N * 2 + (j - 1) * N + k;
  c4 = N * N * 3 + (((i - 1) / 3) * 3 + (j - 1) / 3) * N + k;
}
inline void link(int r, int c) {
  ++S[C[++size] = c];
  X[size] = r;
  D[size] = D[c];
  U[D[c]] = size;
  U[size] = c;
  D[c] = size;
  if (H[r] == -1)
    H[r] = L[size] = R[size] = size;
  else {
    R[size] = R[H[r]];
    L[R[H[r]]] = size;
    L[size] = H[r];
    R[H[r]] = size;
  }
}
inline void remove(int c) {
  L[R[c]] = L[c];
  R[L[c]] = R[c];
  for (int i = D[c]; i != c; i = D[i])
    for (int j = R[i]; j != i; j = R[j])
      D[U[j]] = D[j], U[D[j]] = U[j], --S[C[j]];
}
inline void resume(int c) {
  for (int i = U[c]; i != c; i = U[i])
    for (int j = L[i]; j != i; j = L[j]) ++S[C[D[U[j]] = U[D[j]] = j]];
  L[R[c]] = R[L[c]] = c;
}
void dance(int k) {
  if (!R[0]) {
    int ls = 0;
    for (int i = 0; i < k; ++i)
      ls += fen[(X[Q[i]] - 1) / N + 1] * ((X[Q[i]] - 1) % N + 1);
    ans = ans > ls ? ans : ls;
    return;
  }
  int tmp = mm, c;
  for (int i = R[0]; i; i = R[i])
    if (S[i] < tmp) tmp = S[c = i];
  remove(c);
  for (int i = D[c]; i != c; i = D[i]) {
    Q[k] = i;
    for (int j = R[i]; j != i; j = R[j]) remove(C[j]);
    dance(k + 1);
    for (int j = L[i]; j != i; j = L[j]) resume(C[j]);
  }
  resume(c);
}
int main() {
  int r, c1, c2, c3, c4;
  prepare(mn, N * N * 4);
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j) {
      scanf("%d", &map[i][j]);
      if (map[i][j]) {
        place(r, c1, c2, c3, c4, i, j, map[i][j]);
        link(r, c1);
        link(r, c2);
        link(r, c3);
        link(r, c4);
        v[c1] = v[c2] = v[c3] = v[c4] = 1;
      }
    }
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      for (int k = 1; k <= N; ++k) {
        place(r, c1, c2, c3, c4, i, j, k);
        if (v[c1] || v[c2] || v[c3] || v[c4]) continue;
        link(r, c1);
        link(r, c2);
        link(r, c3);
        link(r, c4);
      }
  dance(0);
  printf("%d", ans);
  return 0;
}