#include <cstdio>
#include <cstring>
#define reg register
#define f(i, s, t) for (reg int i = s; i != t; i++)

typedef long long ll;
int H, W;
ll f[2][1 << 11];
bool ins[1 << 11];

int main() {
  while (1) {
    scanf("%d%d", &H, &W);
    if (H == 0) return 0;
    f(i, 0, 1 << W) {
      bool cnt = 0, odd = 0;
      f(j, 0, W) if (i >> j & 1) odd |= cnt, cnt = 0;
      else cnt ^= 1;
      ins[i] = odd | cnt ? 0 : 1;
    }
    f[0][0] = 1;
    f(i, 1, H + 1) f(j, 0, 1 << W) {
      f[i % 2][j] = 0;
      f(k, 0, 1 << W) if ((j & k) == 0 && ins[j | k]) f[i % 2][j] +=
          f[(i - 1) % 2][k];
    }
    printf("%lld\n", f[H % 2][0]);
    memset(f, 0, sizeof(f));
  }
}
