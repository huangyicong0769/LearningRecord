
#include <iostream>

#include <cstdio>

#include <cstring>

#include <vector>

#include <queue>

#include <cmath>

#include <algorithm>

#include <map>

#include <ctime>

#define MAXN 212222

#define MAXM 6122222

#define INF 1000000001

using namespace std;

int n;

int tt, e;

struct node
{

    int v, w, next;

} edge[MAXN * 2];

int head[MAXN];

struct Trie
{

    int next[2];

    void init()
    {

        memset(next, 0, sizeof(next));
    }

} trie[MAXM];

int val[MAXN], vis[MAXN];

void addEdge(int u, int v, int w)

{

    edge[e].v = v;
    edge[e].next = head[u];
    edge[e].w = w;
    head[u] = e++;

    edge[e].v = u;
    edge[e].next = head[v];
    edge[e].w = w;
    head[v] = e++;
}

void add(int x)
{

    int u = 0, ind;

    for (int i = 30; i >= 0; i--)
    {

        if (x & (1 << i))
        {

            ind = 1;
        }
        else
            ind = 0;

        if (!trie[u].next[ind])
        {

            trie[u].next[ind] = ++tt;

            trie[tt].init();
        }

        u = trie[u].next[ind];
    }
}

int gao(int x)
{

    int u = 0, ind, num = 0;

    for (int i = 30; i >= 0; i--)
    {

        if (x & (1 << i))
            ind = 0;

        else
            ind = 1;

        if (trie[u].next[ind])
        {

            num |= (1 << i);

            u = trie[u].next[ind];
        }
        else
            u = trie[u].next[!ind];
    }

    return num;
}

void dfs(int u, int x)
{

    val[u] = x;

    vis[u] = 1;

    for (int i = head[u]; i != -1; i = edge[i].next)
    {

        int v = edge[i].v;

        int w = edge[i].w;

        if (!vis[v])
        {

            dfs(v, x ^ w);
        }
    }
}

int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    while (scanf("%d", &n) != EOF)
    {

        int u, v, w;

        for (int i = 0; i <= n; i++)
            vis[i] = 0;

        e = 0;

        memset(head, -1, sizeof(head));

        for (int i = 1; i < n; i++)
        {

            scanf("%d%d%d", &u, &v, &w);

            u++;
            v++;

            addEdge(u, v, w);
        }

        tt = 0;

        trie[0].init();

        dfs(1, 0);

        int ans = 0;

        for (int i = 1; i <= n; i++)
        {

            ans = max(ans, gao(val[i]));

            add(val[i]);
        }

        printf("%d\n", ans);
    }

    return 0;
}
