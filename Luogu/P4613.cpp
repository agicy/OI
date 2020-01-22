#include <algorithm>
#include <cstdio>
using std::sort;

int n, a[101], b[101];

int main(void)
{
    register int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    for (i = 1; i <= n; ++i)
        if (a[i] > b[i])
            return puts("NE"), 0;
    return puts("DA"), 0;
}