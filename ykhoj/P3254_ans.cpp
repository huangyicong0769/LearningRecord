//By XiaoLe
//From CH1808 Milking Grid
//Others
//USACO 2003 Fall
//POJ 2185
//2019-1-27 13:42:37

#include <cstdio>
#include <cstring>
using namespace std;

char s[10010][80];
int next[10010], r, c;

int read(char *s) {
	int len = 0;
	char c = getchar();
	while (c < 'A' || c > 'Z') {
		if (c == EOF) return EOF;
		c = getchar();
	}
	while (c >= 'A' && c <= 'Z') s[len++] = c, c = getchar();
	return len;
}

bool checkWidth(int x, int y) {
	for (int i = 1; i <= r; ++i) if (s[i][x] != s[i][y]) return false;
	return true;
}

bool checkHeight(int x, int y) {
	for (int i = 1; i <= c; ++i) if (s[x][i] != s[y][i]) return false;
	return true;
}

int getWidth() {
	next[1] = 0;
	for (int i = 2, j = 0; i <= c; ++i) {
		while (j > 0 && !checkWidth(i, j + 1)) j = next[j];
		if (checkWidth(i, j + 1)) ++j;
		next[i] = j;
	}
	return c - next[c];
}

int getHeight() {
	next[1] = 0;
	for (int i = 2, j = 0; i <= r; ++i) {
		while (j > 0 && !checkHeight(i, j + 1)) j = next[j];
		if (checkHeight(i, j + 1)) ++j;
		next[i] = j;
	}
	return r - next[r];
}

int main() {
	scanf("%d%d", &r, &c);
	for (int i = 1; i <= r; ++i) read(s[i] + 1);
	printf("%d\n", getWidth() * getHeight());
	return 0;
}