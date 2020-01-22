#include <cstdio>
#include <cstring>
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)

static char buf[100000], *p1 = buf, *p2 = buf;
bool vis[50001];

inline int read(void)
{
    register char ch = getchar();
    register int sum = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while ('0' <= ch && ch <= '9')
        sum = (sum << 1) + (sum << 3) + ch - '0', ch = getchar();
    return sum;
}

int solve(int, int, int);

int main(void)
{
    register int T, ans, p, a, b;
    T = read();
    while (T--)
    {
        p = read(), a = read(), b = read();
        ans = solve(a, b, p);
        if (ans != -1)
            printf("%d\n", ans);
        else
            puts("Couldn't Produce!");
        if (T)
            memset(vis, false, sizeof(vis));
    }
    return 0;
}

int solve(int a, int b, int p)
{
    register int ans = 0, x = 1;
    while (true)
        if (b == x)
            return ans;
        else if (vis[x])
            return -1;
        else
        {
            vis[x] = true;
            ++ans;
            x *= a;
            if (x >= p)
                x %= p;
        }
}
