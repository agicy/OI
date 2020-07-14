#include <algorithm>
#include <cstdio>
using std::sort;

int n, a[11];

int main(void)
{
    register int i, ans;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    ans = a[n];
    sort(a + 1, a + n + 1);
    printf("%d\n", ans ^ a[n]);
    return 0;
}