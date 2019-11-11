#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;

stack<int> wi, hi;
int a[1010][1010], h[1010][1010];

inline int read() {
	char c = getchar(); int num = 0; bool flag = false;
	while (c < '0' || c > '9') { if (c == '-') flag = true; if (c == EOF) return EOF; c = getchar(); }
	while (c >= '0' && c <= '9') num = num * 10 + (c - '0'), c = getchar();
	return num * (flag ? -1 : 1);
}

inline int readBlock() {
	char c = getchar();
	while (c != 'R' && c != 'F') { if (c == EOF) return EOF; c = getchar(); }
	if (c == 'R') return 0;
	 else return 1;
}

void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar((x % 10) + '0');
}

inline void writeln(const int &x) {
	write(x), puts("");
}

inline void countHeight(const int &M, const int &N) {
	for (int i = 0; i < N; ++i) if (a[0][i]) h[0][i] = 1; else h[0][i] = 0;
	for (int i = 1; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			if (a[i][j]) h[i][j] = h[i - 1][j] + 1;
			  else h[i][j] = 0;
		}
	}
}


inline int getValue(const int &x, const int &N) {
	while (!wi.empty()) wi.pop();
	while (!hi.empty()) hi.pop();
	hi.push(0), wi.push(0);
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		if (h[x][i] >= hi.top()) {
			hi.push(h[x][i]);
			wi.push(1);
		} else {
			int height, newWidth = 0, ans = 0;
			while (hi.size() > 1 && hi.top() > h[x][i]) {
				height = hi.top(), hi.pop();
				newWidth += wi.top(), wi.pop();
				ans = max(ans, height * newWidth);
			}
			ans = max(ans, h[x][i] * (newWidth + 1));
			hi.push(h[x][i]);
			wi.push(newWidth + 1);
			ret = max(ret, ans);
			
		}
	}
	int height, newWidth = 0;
	while (hi.size() > 1) {
		height = hi.top(), hi.pop();
		newWidth += wi.top(), wi.pop();
		ret = max(ret, height * newWidth);
	}
	return ret;
}

inline void doit() {
	int M = read(), N = read();
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = readBlock();
	int ans = 0;
	countHeight(M, N);
	for (int i = 0; i < M; ++i) ans = max(getValue(i, N), ans);
	writeln(ans * 3);
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif // LOCAL
	int T = read();
	for (int t = 0; t < T; ++t) doit();
	return 0;
}