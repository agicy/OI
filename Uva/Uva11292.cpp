#include <algorithm>
#include <cstdio>
using std::sort;

const int MAXN = 20000 + 5, MAXM = 20000 + 5;

int n, m;
int a[MAXN], b[MAXM];

int main(void)
{
    register int i, cur, sum;
    while (scanf("%d%d", &n, &m) != EOF && n && m)
    {
        for (i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (i = 1; i <= m; ++i)
            scanf("%d", &b[i]);
        sort(a + 1, a + n + 1);
        sort(b + 1, b + m + 1);
        sum = 0;
        cur = 1;
        for (i = 1; i <= m; ++i)
            if (b[i] >= a[cur])
            {
                sum += b[i];
                if (++cur > n)
                    break;
            }
        if (cur <= n)
            puts("Loowater is doomed!");
        else
            printf("%d\n", sum);
    }
    return 0;
}