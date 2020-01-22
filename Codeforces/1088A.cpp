#include <cstdio>

int x;

int main(void)
{
    scanf("%d", &x);
    if (x == 1)
        puts("-1");
    else
        printf("%d %d\n", x, x);
    return 0;
}