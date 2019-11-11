//By XiaoLe
//From ykhoj P3257 生日礼物
//Others
//BZOJ 2288
//CH1812
//2019-1-31 13:21:53

#include <cstdio>
#include <queue>
#include <cmath>
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

typedef pair<int, int> pir;
priority_queue<pir, vector<pir>, greater<pir> > q;
int a[100010], l[100010], r[100010], n, cnt, m, x, last = -1, ans = 0;
bool flag = false, mark[100010];

void remove(int pos) {
	r[l[pos]] = r[pos], l[r[pos]] = l[pos];
	mark[pos] = true;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
	n = read(), m = read();
	if (n == EOF || m == EOF || n == 0) puts("0");

	for (int i = 1; i <= n; ++i) {
		x = read();
		if (!x) continue;
		if ((long long) last * x >= 0) a[cnt] += x;
		  else a[++cnt] = x;
		last = x;
	}
	n = cnt, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] > 0) ++cnt, ans += a[i];
		l[i] = i - 1, r[i] = i + 1;
		q.push(make_pair(abs(a[i]), i));
	}
	while (cnt > m) {
		while (mark[q.top().second]) q.pop();
		x = q.top().second, q.pop();
        printf("%d %d\n", x, a[x]);
		if (a[x] > 0 || l[x] && r[x] <= n) {
			--cnt, ans -= abs(a[x]);
			a[x] += a[l[x]] + a[r[x]], remove(l[x]), remove(r[x]);
			q.push(make_pair(abs(a[x]), x));
		} else remove(x);
	}
	printf("%d\n", ans);
	return 0;
}