#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int di[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct Point
{
    int x, y;
};

vector<Point> v;
queue<Point> q1, q2;

bool d1[810][810], d2[810][810];
int N, M;
char c[810][810];

inline bool legal(const Point &, const int &);
inline int bfs();

int main()
{
    int T;
    for (scanf("%d", &T); T; T--)
    {
        v.clear();
        while (q1.size())
            q1.pop();
        while (q2.size())
            q2.pop();
        scanf("%d%d", &N, &M);
        for (register int i = 0; i < N; i++)
            scanf("%s", c[i]);
        for (register int i = 0; i < N; i++)
            for (register int j = 0; j < M; j++)
                if (c[i][j] == 'M')
                    q1.push((Point){i, j});
                else if (c[i][j] == 'G')
                    q2.push((Point){i, j});
                else if (c[i][j] == 'Z')
                    v.push_back((Point){i, j});
        if (q1.front().x == q2.front().x && q1.front().y == q2.front().y)
            puts("0");
        else
            printf("%d\n", bfs());
    }
}

inline bool legal(const Point &a, const int &b)
{
    if (a.x < 0 || a.y < 0 || a.x >= N || a.y >= M)
        return false;
    if (c[a.x][a.y] == 'X')
        return false;
    for (register int i = 0; i < v.size(); i++)
        if (abs(v[i].x - a.x) + abs(v[i].y - a.y) <= b * 2)
            return false;
    return true;
}

inline int bfs()
{
    memset(d1, 0, sizeof(d1));
    memset(d2, 0, sizeof(d2));
    d1[q1.front().x][q1.front().y] = 1;
    d2[q2.front().x][q2.front().y] = 1;
    for (register int ans = 1; q1.size() || q2.size(); ans++)
    {
        for (register int _ = 0; _ < 3; _++)
        {
            for (register int s1 = q1.size(); s1; s1--)
            {
                Point m = q1.front();
                q1.pop();
                if (!legal(m, ans)) continue;
                for (register int k = 0; k < 4; k++)
                {
                    Point nex;
                    nex.x = m.x + di[k][0];
                    nex.y = m.y + di[k][1];
                    if (legal(nex, ans) && !d1[nex.x][nex.y])
                    {
                        d1[nex.x][nex.y] = 1;
                        q1.push(nex);
                    }
                }
            }
        }
        for (register int s2 = q2.size(); s2; s2--)
        {
            Point f = q2.front();
            q2.pop();
            if (!legal(f, ans)) continue;
            for (register int k = 0; k < 4; k++)
            {
                Point nex;
                nex.x = f.x + di[k][0];
                nex.y = f.y + di[k][1];
                if (legal(nex, ans) && !d2[nex.x][nex.y])
                {
                    if (d1[nex.x][nex.y])
                        return ans;
                    d2[nex.x][nex.y] = 1;
                    q2.push(nex);
                }
            }
        }
    }
    return -1;
}