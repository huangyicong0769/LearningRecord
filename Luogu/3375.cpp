#include <cstdio>
#include <cstring>
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 1000006;
char s1[SN], s2[SN];
class KMP {
  char* cs;
  int nxt[SN];

  il void init() {
    reg m = strlen(cs + 1);
    for (reg i = 2, j = 0; i <= m; i++) {
      while (j && cs[i] != cs[j + 1]) j = nxt[j];
      if (cs[i] == cs[j + 1]) j++;
      nxt[i] = j;
    }
  }

 public:
  KMP(char* s) { cs = s, init(); }

  il void find(char* s) {
    reg m = strlen(cs + 1), n = strlen(s + 1);
    for (reg i = 1, j = 0; i <= n; i++) {
      while (j && s[i] != cs[j + 1]) j = nxt[j];
      if (s[i] == cs[j + 1]) j++;
      if (j == m) {
        printf("%d\n", i - m + 1);
        j = nxt[j];
      }
    }
  }

  il void printNxt() {
    reg m = strlen(cs + 1);
    f(i, 1, m) printf("%d ", nxt[i]);
    puts("");
  }
};

int main() {
  scanf("%s%s", s1 + 1, s2 + 1);
  KMP cur(s2);
  cur.find(s1);
  cur.printNxt();
}