#include <cstdio>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, Q, dis[41][41];

int main(void)
{
    register int i, j, k;
    memset(dis, 0X3F, sizeof(dis));
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        dis[i][i] = 0;
    while (m--)
    {
        static int u, v;
        scanf("%d%d", &u, &v);
        dis[u][v] = dis[v][u] = 1;
    }
    scanf("%d", &Q);
    for (k = 1; k <= n; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j < i; ++j)
                if (k != i && k != j)
                {
                    dis[i][j] = dis[j][i] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
    while (Q--)
    {
        static int u, v;
        scanf("%d%d", &u, &v);
        for (i = 1; i <= n; ++i)
            if (dis[u][i] + dis[i][v] == dis[u][v])
                printf("%d ", i);
        putchar('\n');
    }
    return 0;
}