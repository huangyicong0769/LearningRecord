#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int read() {
	int num = 0; char c = getchar(); bool flag = false;
	while (c < '0' || c > '9') {
		if (c == EOF) return EOF;
		if (c == '-') flag = true;
		c = getchar();
	}
	while (c >= '0' && c <= '9') num = num * 10 + (c - '0'), c = getchar();
	return num * (flag ? -1 : 1);
}

int w, n, a[110], ans;
vector<int> s;

void dfs_1(int v, int current) {
    if (current < 1) return;
	s.push_back(v);
	if (v > w - a[current]) return;
	for (int i = current; i > 0; --i) if (v <= w - a[i]) dfs_1(v + a[i], i - 1); else break;
}

inline void check(const int &v) {
	int l = 1, r = s.size() - 1;
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (s[mid] > w - v) r = mid - 1;
		if (s[mid] <= w - v) l = mid + 1;
	}
	if (s[mid] > w - v) --mid;
	ans = max(s[mid] + v, ans);
}

void dfs_2(int v, int current) {
	check(v);
	if (ans == w) return;
	if (current > n || v > w - a[current]) return;
	for (int i = current; i <= n; ++i) if (v <= w - a[i]) dfs_2(v + a[i], i + 1); else break;
}

bool cmp(const int &n1, const int &n2) {
    return n1 > n2;
}

int main() {
	w = read(), n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a, a + n + 1, cmp);
	dfs_1(0, n / 2 + 1);
	sort(s.begin(), s.end());
	dfs_2(0, n / 2 + 2);
	printf("%d\n", ans);
	return 0;
}