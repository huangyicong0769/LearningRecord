#include <stdio.h>
#include <map>
using namespace std;
#define x 937728547
#define y 185827533
#define uint unsigned int

map<uint, int> p;
uint k[1005][1005], temp[1005][1005], px[1005] = {1}, py[1005] = {1};

int main(void)
{
	int n, m, a, b, i, j, q;
	for (i = 1; i <= 1005; i++)
	{
		px[i] = px[i - 1] * x;
		py[i] = py[i - 1] * y;
	}
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
			scanf("%1u", &k[i][j]);
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
			k[i][j] += k[i][j - 1] * x;
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			k[i][j] += k[i - 1][j] * y;
			if (i >= a && j >= b)
				p[k[i][j] - k[i - a][j] * py[a] - k[i][j - b] * px[b] + k[i - a][j - b] * py[a] * px[b]] = 1;
		}
	}
	scanf("%d", &q);
	while (q--)
	{
		for (i = 1; i <= a; i++)
		{
			for (j = 1; j <= b; j++)
				scanf("%1u", &temp[i][j]);
		}
		for (i = 1; i <= a; i++)
		{
			for (j = 1; j <= b; j++)
				temp[i][j] += temp[i][j - 1] * x;
		}
		for (i = 1; i <= a; i++)
		{
			for (j = 1; j <= b; j++)
				temp[i][j] += temp[i - 1][j] * y;
		}
		if (p.count(temp[a][b]))
			printf("1\n");
		else
			printf("0\n");
	}
	return 0;
}
