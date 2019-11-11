// 题目大意：给出两个集合的点，问这两个集合之间最近的点对的距离是多少。

// 思路：先要知道平面最近点对的分治算法，剩下的就简单了，只需要在更新答案的时候判断一下两个点是否属于两个集合就可以了。

// 分治算法总是十分神奇的。

// 对于平面最近点对，首先按照x坐标排序，然后递归进行分治，每次分治时，先获得分治得到的结果，然后按照这个结果来计算本区间。由于我们只需要计算答案小于这个结果的点对就行了，其中(l,mid)和(mid + 1,r)我们已经得到答案，只需要统计一个点在(l,mid)，另一个点在(mid + 1,r)的所有点对了。但是这还是很大。

// 有一个强剪枝，设立中轴为(X[mid] + X[mid + 1]) / 2，我们只需要统计在这个中轴两侧不超过之前算过的最小值的点就可以了，因为其他的点对不可能更新答案。

// 还有一个剪枝，每次找到这些点之后，再按照y坐标排序，之后发现y坐标相差超过之前算过的最小值的点对也肯定不能更新答案，对于一个点来说能够更新答案的点在另一侧是一个单调的区间，只需要一个指针扫一下就行了。

// CODE：

#include <cmath>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAX 200010
#define INF 1e15
using namespace std;

struct Point{
	double x,y;
	bool p;
	
	bool operator <(const Point &a)const {
		return x < a.x;
	}
	void Read(bool _) {
		scanf("%lf%lf",&x,&y);
		p = _;
	}
}point[MAX],L[MAX],R[MAX];

int points;

inline double Calc(const Point &p1,const Point &p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool cmp(const Point &p1,const Point &p2)
{
	return p1.y < p2.y;
}

double Solve(int l,int r)
{
	double re = INF;
	if(r - l <= 2) {
		for(int i = l; i <= r; ++i)
			for(int j = i + 1; j <= r; ++j)
				if(point[i].p != point[j].p)
					re = min(re,Calc(point[i],point[j]));
		return re;
	}
	int mid = (l + r) >> 1;
	re = min(re,Solve(l,mid));
	re = min(re,Solve(mid + 1,r));
	double x = (point[mid].x + point[mid + 1].x) / 2.0;
	int pl = mid,pr = mid + 1;
	int ltop = 0,rtop = 0;
	while(x - point[pl].x <= re && pl >= l)	L[++ltop] = point[pl--];
	while(point[pr].x - x <= re && pr <= r)	R[++rtop] = point[pr++];
	sort(L + 1,L + ltop + 1,cmp);
	sort(R + 1,R + rtop + 1,cmp);
	int start = 1;
	for(int i = 1; i <= ltop; ++i) {
		while(L[i].y - R[start].y > re)	++start;
		for(int j = start; R[j].y - L[i].y < re && j <= rtop; ++j)
			if(L[i].p != R[j].p)
				re = min(re,Calc(L[i],R[j]));
	}
	return re;
}

int main()
{
#ifdef DEBUG
      freopen("input.txt", "r", stdin);
#endif // DEBUG
	int T;
	for(cin >> T; T--;) {
		scanf("%d",&points);
		for(int i = 1; i <= points; ++i)
			point[i].Read(true);
		for(int i = points + 1; i <= (points << 1); ++i)
			point[i].Read(false);
		points <<= 1;
		sort(point + 1,point + points + 1);
		printf("%.3f\n",Solve(1,points));
	}
	return 0;		
}