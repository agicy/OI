#include <cstdio>
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline int read(void)
{
    register char ch = getchar();
    register int sum = 0;
    while (!(ch >= '0' && ch <= '9'))
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        sum = (sum << 1) + (sum << 3) + ch - 48, ch = getchar();
    return sum;
}

int last[200001], sum[200001], cnt[200001];

int main(void)
{
    register int n, p, color, price, now, ans = 0, i;
    n = read(), read(), p = read();
    for (i = 1; i <= n; ++i)
    {
        color = read(), price = read();
        if (price <= p)
            now = i;
        if (now >= last[color])
            sum[color] = cnt[color];
        ++cnt[color];
        last[color] = i;
        ans += sum[color];
    }
    printf("%d\n", ans);
    return 0;
}