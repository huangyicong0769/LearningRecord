#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

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

struct MyStatus {
	int city;
	int fuel;
	int cost;
	bool operator<(const MyStatus &ms) const {
		return ((this -> cost) > ms.cost) || ((this -> cost) == ms.cost && (this -> fuel) < ms.fuel);
	}
} current;

struct Road {
	int to;
	int cost;
};

vector<Road> v[1010];
int d[1010][110], p[1010];
priority_queue<MyStatus> q;

inline void doit() {
	while (!q.empty()) q.pop();
	memset(d, 0x7f7f7f7f, sizeof(d));
	int c = read(), s = read(), e = read(), ci, co, fu;
	d[s][0] = 0;
	q.push((MyStatus){s, 0, 0});
	while (!q.empty()) {
		current = q.top(); q.pop();
		ci = current.city, co = current.cost, fu = current.fuel;
		if (ci == e) {
			printf("%d\n", co);
			return;
		}
		if (d[ci][fu] < co) continue;
		if (fu < c && co + p[ci] < d[ci][fu + 1]) {
			d[ci][fu + 1] = co + p[ci];
			q.push((MyStatus){ci, fu + 1, co + p[ci]});
		}
		for (int i = 0; i < v[ci].size(); ++i) {
			if (fu >= v[ci][i].cost) {
				if (d[v[ci][i].to][fu - v[ci][i].cost] > co) {
					d[v[ci][i].to][fu - v[ci][i].cost] = co;
					q.push((MyStatus){v[ci][i].to, fu - v[ci][i].cost, co});
				}
			}
		}
	}
	puts("impossible");
}

int main() {
	int n = read(), m = read();
	for (int i = 0; i < n; ++i) p[i] = read();
	for (int i = 0; i < m; ++i) {
		int x = read(), y = read(), z = read();
		v[x].push_back((Road){y, z});
		v[y].push_back((Road){x, z});
	}
	int T = read();
	for (int t = 0; t < T; ++t) doit();
	return 0;
}