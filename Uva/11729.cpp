#include <algorithm>
#include <cstdio>
using std::sort;
#define max(a, b) ((a) > (b) ? (a) : (b))

const int MAXN = 1000 + 5;

struct Node
{
    int b, j;
    void Read(void)
    {
        scanf("%d%d", &b, &j);
        return;
    }
    bool operator<(Node &a) const
    {
        return j > a.j;
    }
};

int n;
Node a[MAXN];

int main(void)
{
    register int Case = 0, i, sum, ans;
    while (scanf("%d", &n) != EOF && n)
    {
        ans = sum = 0;
        for (i = 1; i <= n; ++i)
            a[i].Read();
        sort(a + 1, a + n + 1);
        for (i = 1; i <= n; ++i)
        {
            ans = max(ans, sum + a[i].b + a[i].j);
            sum += a[i].b;
        }
        printf("Case %d: %d\n", ++Case, ans);
    }
    return 0;
}