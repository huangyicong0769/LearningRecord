#include <bits/stdc++.h>
using std::swap;

typedef unsigned long long ull;

int main(){
  int n;
  scanf("%d", &n);
  ull a[n + 1] = {0};
  for (register int i = 0; i < n; i++) scanf("%lld", a + i);
  int t;
  for (register int i = 0; i < n; i++){
    for (register int j = i + 1; j < n; j++)
      if (a[j] > a[i]) swap(a[i], a[j]);
    if (a[i] == 0) break;
    for (register int k = 51; k >= 0; k--)
      if (a[i] >> k & 1){
        for (register int j = 1; j <= n; j++)
          if (i != j && (a[j] >> k & 1)) a[j] ^= a[i];
        break;
      }
  }
  ull ans = 0;
  for (register int i = 0; i < n && a[i]; i++){
    ans = std::max(ans, ans^a[i]);
  }
  printf("%lld\n", ans);
}