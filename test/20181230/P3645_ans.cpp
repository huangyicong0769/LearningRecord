#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> c[60];

int read() {
    int num = 0; char c = getchar(); bool flag = false;
    while (c < '0' || c > '9') {
        if (c == '-') flag = true;
        if (c == EOF) return EOF;
        c = getchar();
    }
    while (c >= '0' && c <= '9') num = num * 10 + (c - '0'), c = getchar();
    return num * (flag ? -1 : 1);
}

int skip, ans = 2147483640, n, k, x, MIN = 2147483640;

void dfs(int l, int r, int current) {
    if (current >= k) ans = min(ans, r - l);
    if (c[current].size() == 1) {
        dfs(min(l, c[current][0]), max(r, c[current][1]), current + 1);
        return;
    }
    int mid, le = 0, ri = c[current].size() - 1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (c[current][mid] <= r && c[current][mid] >= l) {
            dfs(l, r, current + 1);
            return;
        }
        if (mid != c[current].size() - 1 && c[current][mid] < l && c[current][mid + 1] > r) {
            dfs(c[current][mid], r, current + 1), dfs(l, c[current][mid + 1], current + 1);
            return;
        }
        if (c[current][mid] > r) ri = mid - 1;
        if (c[current][mid] < l) le = mid + 1;
    }
}

int main() {
    n = read(), k = read();
    for (int i = 0; i < k; ++i) {
        int cnt = read();
        if (cnt < MIN) {
            MIN = cnt;
            skip = i;
        }
        for (int j = 0; j < cnt; ++j) x = read(), c[i].push_back(x);   
    }
    for (int i = 0; i < c[skip].size(); ++i) dfs(c[skip][i], c[skip][i], 0);
    printf("%d\n", ans);
    return 0;
}
