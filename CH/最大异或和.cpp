// ykhoj 3359
// luogu 4735
// BZoj 3261
#include <cstdio>
#include <iostream>
#define SIZE 600006
#define reg register
#define f(a, b, c) for (reg int a = b; a <= c; a++)
using namespace std;

int trie[SIZE * 24][2], latest[SIZE * 24], s[SIZE], root[SIZE], N, M, tot;

void insert(int k, int i, int p, int q) {
  if (k < 0) {
    latest[q] = i;
    return;
  }
  int c = s[i] >> k & 1;
  if (p) trie[q][c ^ 1] = trie[p][c ^ 1];
  trie[q][c] = ++tot;
  insert(k - 1, i, trie[p][c], trie[q][c]);
  latest[q] = max(latest[trie[q][c]], latest[trie[q][c ^ 1]]);
}

int ask(int k, int q, int val, int limit) {
  if (k < 0) return val ^ s[latest[q]];
  int c = val >> k & 1;
  if (latest[trie[q][c ^ 1]] >= limit)
    return ask(k - 1, trie[q][c ^ 1], val, limit);
  else
    return ask(k - 1, trie[q][c], val, limit);
}

int main() {
  scanf("%d%d", &N, &M);
  latest[0] = -1;
  root[0] = ++tot;
  insert(23, 0, 0, root[0]);
  f(i, 1, N) {
    int x;
    scanf("%d", &x);
    s[i] = s[i - 1] ^ x;
    root[i] = ++tot;
    insert(23, i, root[i - 1], root[i]);
  }
  f(i, 1, M) {
    char op[2];
    scanf("%s", op);
    if (op[0] == 'A') {
      int x;
      scanf("%d", &x);
      root[++N] = ++tot;
      s[N] = s[N - 1] ^ x;
      insert(23, N, root[N - 1], root[N]);
    } else {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      printf("%d\n", ask(23, root[r - 1], s[N] ^ x, l - 1));
    }
  }
}
