#include <cstdio>
#define INF 0X3F3F3F3F
#define max(a, b) ((a) > (b) ? (a) : (b))

int n, a[100002];

int main(void)
{
    register int i, ans = 1, temp = 1;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    a[0] = INF;
    for (i = 1; i <= n + 1; ++i)
    {
        if (a[i] > a[i - 1])
            ++temp;
        else
        {
            ans = max(ans, temp);
            temp = 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}