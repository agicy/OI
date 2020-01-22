#include <cstdio>
#define MOD 80112002

int n, m, ans;
int cnt, head[5001], to[500001], Next[500001];
int Q[5001], _head, _tail;
int inDeg[5001], outDeg[5001];
int dp[5001];

void Add_Edge(int, int);
void Topo(void);

int main(void)
{
    register int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
    {
        static int a, b;
        scanf("%d%d", &a, &b);
        ++inDeg[b];
        ++outDeg[a];
        Add_Edge(a, b);
    }
    Topo();
    printf("%d\n", ans);
    return 0;
}

void Add_Edge(int f, int t)
{
    Next[++cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt;
    return;
}

void Topo(void)
{
    register int i, ID, To;
    for (i = 1; i <= n; ++i)
        if (!inDeg[i])
        {
            dp[i] = 1;
            Q[_tail++] = i;
        }
    while (_head < _tail)
    {
        ID = Q[_head++];
        for (i = head[ID]; i; i = Next[i])
        {
            To = to[i];
            --inDeg[To];
            dp[To] += dp[ID];
            if (!inDeg[To])
            {
                if (!outDeg[To])
                {
                    ans += dp[To];
                    ans %= MOD;
                    continue;
                }
                Q[_tail++] = To;
            }
        }
    }
    return;
}
