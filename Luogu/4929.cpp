#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define il inline

const int SN = 250506;
int N, M, cnt, ans, head[SN], colSum[SN], ansk[SN], l[SN], r[SN], u[SN], d[SN],
    col[SN], row[SN];

il void init(int m) {
  f(i, 0, m) {
    r[i] = i + 1;
    l[i] = i - 1;
    u[i] = d[i] = i;
  }
  r[m] = 0, l[0] = m;
  ms(head, -1), ms(colSum, 0);
  cnt = m + 1;
}

il void link(int R, int C) {
  colSum[C]++;
  row[cnt] = R, col[cnt] = C;
  u[cnt] = C, d[cnt] = d[C];
  u[d[C]] = cnt;
  d[C] = cnt;
  if (head[R] == -1)
    head[R] = r[cnt] = l[cnt] = cnt;
  else {
    r[cnt] = head[R];
    l[cnt] = l[head[R]];
    r[l[head[R]]] = cnt;
    l[head[R]] = cnt;
  }
  cnt++;
}

il void remove(int C) {
  r[l[C]] = r[C], l[r[C]] = l[C];
  for (reg i = d[C]; i != C; i = d[i])
    for (reg j = r[i]; j != i; j = r[j]) {
      u[d[j]] = u[j];
      d[u[j]] = d[j];
      colSum[col[j]]--;
    }
}

il void resume(int C) {
  for (reg i = u[C]; i != C; i = u[i])
    for (reg j = l[i]; j != i; j = l[j]) {
      u[d[j]] = j;
      d[u[j]] = j;
      colSum[col[j]]++;
    }
  r[l[C]] = C, l[r[C]] = C;
}

bool dance(int dep) {
  if (r[0] == 0) {
    f(i, 0, dep - 1) printf("%d ", ansk[i]);
    puts("");
    return 1;
  }
  reg c = r[0];
  for (reg i = r[0]; i != 0; i = r[i])
    if (colSum[i] < colSum[c]) c = i;
  remove(c);
  for (reg i = d[c]; i != c; i = d[i]){
    ansk[dep] = row[i];
    for (reg j = r[i]; j != i; j = r[j]) remove(col[j]);
    if (dance(dep + 1)) return 1;
    for (reg j = l[i]; j != i; j = l[j]) resume(col[j]);
  }
  resume(c);
  return 0;
}

int main(){
  scanf("%d%d", &N, &M);
  init(M);
  f(i, 1, N) f(j, 1, M) {
    reg a;
    scanf("%d", &a);
    if (a) link(i, j);
  }
  if (dance(0) == 0) puts("No Solution!");
}