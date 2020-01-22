#include <cstdio>

long long a, b, k;

int main(void)
{
    scanf("%lld%lld%lld", &k, &a, &b);
    if (k <= a)
        puts("1");
    else if (a <= b)
        puts("-1");
    else
        printf("%lld\n", ((k - a) / (a - b) + bool((k - a) % (a - b))) << 1 | 1);
    return 0;
}