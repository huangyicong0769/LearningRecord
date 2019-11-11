#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define SIZE 2006
#define reg register
#define rg reg int
#define f(i, s, t) for (rg i = s; i != t + 1; i++)
using namespace std;

const int INF = 0x3f3f3f3f;
int N, K, A[SIZE], val[SIZE][SIZE], f[SIZE][26];
priority_queue<int> pq1;                              //小堆
priority_queue<int, vector<int>, greater<int> > pq2;  //大堆

int main() {
  // freopen("input.txt", "r", stdin);
  while (scanf("%d%d", &N, &K) && N) {
    f(i, 1, N) scanf("%d", &A[i]);
    f(i, 1, N) {
      while (pq1.size()) pq1.pop();
      while (pq2.size()) pq2.pop();
      rg cnt = 0;
      f(j, i, N) {
        if (pq1.empty() || A[j] <= pq1.top())
          pq1.push(A[j]), cnt -= A[j];
        else
          pq2.push(A[j]), cnt += A[j];
        rg k1 = (j - i + 1) >> 1, k2 = (j - i + 1) - k1;
        while (pq1.size() > k1)
          pq2.push(pq1.top()), cnt += pq1.top() << 1, pq1.pop();
        while (pq2.size() > k2)
          pq1.push(pq2.top()), cnt -= pq2.top() << 1, pq2.pop();
        while (pq1.size() && pq2.size() && pq1.top() > pq2.top()) {
          rg t1 = pq1.top(), t2 = pq2.top();
          pq1.pop(), pq2.pop();
          cnt += t1 << 1, cnt -= t2 << 1;
          pq1.push(t2), pq2.push(t1);
        }
        rg w = cnt;
        if (pq2.size() > pq1.size()) w -= pq2.top();
        val[i][j] = abs((double)w);
        // printf("%d ", w);
      }
      // puts("");
    }
    f(i, 1, N) f(j, 0, K) f[i][j] = INF;
    f(i, 0, N) f(j, 1, K) f(k, 0, i - 1) f[i][j] =
        min(f[i][j], f[k][j - 1] + val[k + 1][i]);
    printf("%d\n", f[N][K]);
  }
}