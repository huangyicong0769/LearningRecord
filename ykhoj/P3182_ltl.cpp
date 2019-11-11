#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

struct Node{
	int value;
	int number;
} c[301];
int n, m, t, x, y, z, f[301][301], g[301][301], h[301];

bool _comp(const Node &n1, const Node &n2) {
	return n1.value < n2.value;
}

int main() {
	cin>>n>>m>>t;
	for (int i = 0; i < n; ++i) {
		cin>>c[i].value;
		c[i].number = i;
	}
	sort(c, c + n, _comp);
	for (int i = 0; i < n; ++i) {
		h[c[i].number]  = i;
	}
	memset(f, 127, sizeof(f));
	memset(g, 127, sizeof(g));
	int MAX = f[0][0];
	for (int i = 0; i < m; ++i) {
		cin>>x>>y>>z;
		--x; --y;
		if (x == y) continue;
		x = h[x]; y = h[y];
		f[x][y] = min(f[x][y], z);
		f[y][x] = f[x][y];
		g[y][x] = g[x][y] = min(g[x][y], f[x][y] + max(c[x].value, c[y].value));
	}
	
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			if (i == k) continue;
			for (int j = 0; j < n; ++j) {
				if (j == k || j == i) continue;
				if (f[i][k] == MAX || f[k][j] == MAX) continue;
				if (f[i][j] > f[i][k] + f[k][j]) {
					f[i][j] = f[i][k] + f[k][j];
					f[j][i] = f[i][j];
					g[j][i] = g[i][j] = min(g[i][j], max(c[i].value, max(c[j].value, c[k].value)) + f[i][j]);
				}
			}
		}
	}
	for (int i = 0; i < t; ++i) {
		cin>>x>>y;
		--x; --y;
		cout<<g[h[x]][h[y]]<<endl;
	}
	return 0;
}