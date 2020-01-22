#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))

bool vis[100001];
int n, m;
int cnt, head[100001], to[500001], Next[500001];
int time, dfn[100001], low[100001];
int Tarjan_cnt, color[100001];
int Stack[100001], top;
int inDeg[100001];

void Add_Edge(int, int);
void Tarjan(int);

int main(void)
{
    register int i, j, To, ans = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
    {
        static int b, e;
        scanf("%d%d", &b, &e);
        Add_Edge(b, e);
    }
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            Tarjan(i);
    for (i = 1; i <= n; ++i)
        for (j = head[i]; j; j = Next[j])
        {
            To = to[j];
            if (color[i] != color[To])
                ++inDeg[color[To]];
        }
    for (i = 1; i <= Tarjan_cnt; ++i)
        if (!inDeg[i])
            ++ans;
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
        } while (To != ID);
    }
    return;
}