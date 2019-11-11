
#include <cstdio>

#include <cstring>

#include <iostream>

#include <algorithm>

using namespace std;

int n, m, k, x, y, kk, a[251][251], f[251][251];

struct node
{

    int val, id;

} v[251];

int read()

{

    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }

    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }

    return x * f;
}

bool operator<(node u, node v)

{

    return u.val < v.val;
}

int main()

{
    freopen("input.txt", "r", stdin);
    n = read();
    m = read();
    k = read();

    for (int i = 1; i <= n; i++)
        v[i] = (node){read(), i};

    memset(a, 127 / 3, sizeof(a));

    memset(f, 127 / 3, sizeof(f));

    for (int i = 1; i <= n; i++)
        f[i][i] = v[i].val;

    sort(v + 1, v + n + 1);

    for (int i = 1; i <= m; i++)

    {

        x = read();
        y = read();
        kk = read();

        a[x][y] = a[y][x] = min(a[x][y], kk);
    }

    for (int z = 1; z <= n; z++)

        for (int i = 1; i <= n; i++)

            for (int j = 1; j <= n; j++)

            {

                kk = v[z].id;
                x = v[i].id;
                y = v[j].id;

                a[x][y] = a[y][x] = min(a[x][y], a[x][kk] + a[kk][y]);

                f[x][y] = f[y][x] = min(f[x][y], a[x][y] + max(v[z].val, max(v[i].val, v[j].val)));
            }

    while (k--)

    {

        x = read();
        y = read();

        printf("%d\n", f[x][y]);
    }

    return 0;
}
