#include <stdio.h>
int main(void)
{
    int n, x = 0;
    scanf("%d", &n);
    int a[10], i, m;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (i = 0; i < n; i++)
    {
        if (m == a[i])
        {
            x = 1;
            printf("%d ", a[i]);
        }
    }
    if (x == 0)
        printf("not");
    return 0;
}