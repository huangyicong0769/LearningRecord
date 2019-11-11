#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
    freopen("input.txt", "w", stdout);
    srand((unsigned)time(0));
    int n = rand() % 10001;
    printf("%d\n",n);
        for (int j = 0; j < n; j++){
            printf("%d %d", rand() % 10000 +1 , rand() % 10000 +1);
        printf("\n");
        }
}