#include <cstdio>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

bool vis[10001];
int n, m, w[10001], f[100001], t[100001];
int cnt, head[10001], to[100001], Next[100001];
int time, dfn[10001], low[10001];
int Tarjan_cnt, color[10001], wealth[10001];
int Stack[10001], top;
int Q[10001], _head, _tail;
int dp[10001], inDeg[10001];

void Add_Edge(int, int);
void Tarjan(int);
void Topo_Init(void);
void Topo(void);

int main(void)
{
    register int i, ans = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (i = 1; i <= m; ++i)
    {
        scanf("%d%d", &f[i], &t[i]);
        Add_Edge(f[i], t[i]);
    }
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            Tarjan(i);
    Topo_Init();
    Topo();
    for (i = 1; i <= Tarjan_cnt; ++i)
        ans = max(ans, dp[i]);
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

void Tarjan(int ID)
{
    register int i, To;
    vis[ID] = true;
    dfn[ID] = low[ID] = ++time;
    Stack[++top] = ID;
    for (i = head[ID]; i; i = Next[i])
    {
        To = to[i];
        if (!dfn[To])
        {
            Tarjan(To);
            low[ID] = min(low[ID], low[To]);
        }
        else if (vis[To])
            low[ID] = min(low[ID], dfn[To]);
        else
            continue;
    }
    if (dfn[ID] == low[ID])
    {
        ++Tarjan_cnt;
        do
        {
            To = Stack[top--];
            vis[To] = false;
            color[To] = Tarjan_cnt;
            wealth[Tarjan_cnt] += w[To];
        } while (To != ID);
    }
    return;
}

void Topo_Init(void)
{
    register int i;
    cnt = 0;
    memset(head, 0, sizeof(head));
    for (i = 1; i <= m; ++i)
        if (color[f[i]] != color[t[i]])
        {
            ++inDeg[color[t[i]]];
            Add_Edge(color[f[i]], color[t[i]]);
        }
    for (i = 1; i <= Tarjan_cnt; ++i)
        if (!inDeg[i])
        {
            Q[_tail++] = i;
            dp[i] = wealth[i];
        }
    return;
}

void Topo(void)
{
    register int i, ID, To;
    while (_head < _tail)
    {
        ID = Q[_head++];
        for (i = head[ID]; i; i = Next[i])
        {
            To = to[i];
            --inDeg[To];
            dp[To] = max(dp[To], dp[ID] + wealth[To]);
            if (!inDeg[To])
                Q[_tail++] = To;
        }
    }
    return;
}