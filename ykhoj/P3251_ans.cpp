//By XiaoLe
//From ykhoj P3251 内存分配
//Others
//CCF NOI 1999
//POJ 1003
//2018-12-30 10:27:34

#include <cstdio>
#include <algorithm>
#include <queue>
#define INT_MAX 2147483647
#define debug(a) cout<<(a)<<endl;
using namespace std;

struct Link{
	int next, pos, memory, runTime, start;
} a[10010];

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

void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar((x % 10) + '0');
}

inline void writeln(const int &x) {
	write(x), puts("");
}

int nextTime = INT_MAX, root, currentTime, maxMemory;
queue<int> q;

inline bool join(const int &pos,const int &joinTime) {
	if ((!root) || a[root].pos - 0 >= a[pos].memory) {
		a[pos].next = root;
		root = pos;
		a[pos].pos = 0;
		a[pos].start = joinTime;
		return true;
	}
	for (int i = root; i ; i = a[i].next) {
		if ((a[i].next ? a[a[i].next].pos : maxMemory) - (a[i].pos + a[i].memory) >= a[pos].memory) {
			a[pos].next = a[i].next, a[pos].pos = a[i].pos + a[i].memory, a[pos].start = joinTime;
			a[i].next = pos;
			return true;
		}
	}
	return false;
}

inline void free() {
	int tempTime = INT_MAX;
	for (int i = root, pre = root; i ; i = a[i].next) {
		if (a[i].start + a[i].runTime == nextTime) {
			if (i == root) root = a[i].next;
			  else a[pre].next = a[i].next;
		} else tempTime = min(tempTime, a[i].start + a[i].runTime), pre = i;
	}
	while ((!q.empty()) && join(q.front(), nextTime)) tempTime = min(tempTime, a[q.front()].start + a[q.front()].runTime), q.pop();
	nextTime = tempTime;
}


int main() {
	int totalQueueJoins = 0, endTime = 0;
	maxMemory = read();
	a[1].start = read(), a[1].memory = read(), a[1].runTime = read(), currentTime = a[1].start;
	for (int i = 1; a[i].start != 0 || a[i].memory != 0 || a[i].runTime != 0; ++i, a[i].start = read(), a[i].memory = read(), a[i].runTime = read(), currentTime = a[i].start) {
		while (currentTime >= nextTime) free();
		if (!join(i, currentTime)) q.push(i), ++totalQueueJoins;
		  else nextTime = min(nextTime, a[i].start + a[i].runTime);
	}
	while (!q.empty()) free();
	endTime = nextTime;
	for (int i = root; i ; i = a[i].next) endTime = max(a[i].start + a[i].runTime, endTime);
	writeln(endTime);
	writeln(totalQueueJoins);
	return 0;
}