#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar((x % 10) + '0');
}

inline void writeln(int x) {
	write(x), puts("");
}

int read() {
	int num = 0; bool flag = false; char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF) return EOF;
		if (c == '-') flag = true;
		c = getchar();	
	}
	while (c >= '0' && c <= '9') num = num * 10 + (c - '0'), c = getchar();
	return num * (flag ? -1 : 1);
}

int a[2010], b[2010], c[2010], n, m;

struct Node {
	int i;
	int j;
	bool last;
	bool operator<(const Node &n1) const {
		return a[this -> i] + b[this -> j] > a[n1.i] + b[n1.j];
	}
} temp, t;

priority_queue<Node> p;

inline void merge() {
	while (!p.empty()) p.pop();
	int tot = 0;
	temp.i = 0, temp.j = 0, temp.last = 0;
	p.push(temp);
	while (tot < n) {
		t = p.top();
		p.pop();
		c[tot++] = a[t.i] + b[t.j];
		if (tot == n) break;
		if (t.i + 1 < n && !t.last) temp.i = t.i + 1, temp.j = t.j, temp.last = false, p.push(temp);
		if (t.j + 1 < n) temp.i = t.i, temp.j = t.j + 1, temp.last = true, p.push(temp);
	}
	
	for (int i = 0; i < n; ++i) a[i] = c[i];
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif // LOCAL
	int t = read();
	for (int task = 0; task < t; ++task) {
		m = read(), n = read();
		if (m >= 1) for (int i = 0; i < n; ++i) a[i] = read();
		sort(a, a + n);
		for (int i = 1; i < m; ++i) {
			for (int j = 0; j < n; ++j) b[j] = read();
			sort(b, b + n);
			merge();
		}
		for (int i = 0; i < n; ++i) write(a[i]), putchar(' ');
		puts("");
	}
	return 0;
}