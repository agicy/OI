#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using std::queue;
using std::sort;
using std::stack;
#define min(a, b) ((a) < (b) ? (a) : (b))

bool vis[100001];
int n, m, x;
int f[1000001], t[1000001], Edge_ID[1000001];
int cnt, head[100001], to[1000001], Next[1000001];
int dfn[100001], low[100001], time;
int color[100001], Tarjan_cnt, Tarjan_num[100001];
int inDeg[100001];
int ans, dis[100001], Way[100001];

queue<int> Q;
stack<int> S;

void Rebuild(void);
void Topo_Init(void);
void Topo(void);
void Tarjan(int);
void Add_Edge(int, int);
bool sort_rule(int, int);

int main(void)
{
    register int i, sum = 0;
    scanf("%d%d%d", &n, &m, &x);
    for (i = 1; i <= m; ++i)
    {
        scanf("%d%d", &f[i], &t[i]);
        Add_Edge(f[i], t[i]);
    }
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            Tarjan(i);
    Rebuild();
    Topo_Init();
    Topo();
    for (i = 1; i <= n; ++i)
        if (dis[i] == dis[ans])
            sum = (sum + Way[i]) % x;
    printf("%d\n%d\n", dis[ans], sum);
    return 0;
}

void Rebuild(void)
{
    register int i, ID;
    for (i = 1; i <= m; ++i)
    {
        Edge_ID[i] = i;
        f[i] = color[f[i]];
        t[i] = color[t[i]];
    }
    sort(Edge_ID + 1, Edge_ID + m + 1, sort_rule);
    cnt = 0;
    memset(head, 0, sizeof(head));
    for (i = 1; i <= m; ++i)
    {
        ID = Edge_ID[i];
        if (f[ID] != t[ID] && (f[ID] != f[Edge_ID[i - 1]] || t[ID] != t[Edge_ID[i - 1]]))
        {
            ++inDeg[t[ID]];
            Add_Edge(f[ID], t[ID]);
        }
    }
    return;
}

void Topo_Init(void)
{
    register int i;
    for (i = 1; i <= Tarjan_cnt; ++i)
        if (!inDeg[i])
        {
            Q.push((int)i);
            dis[i] = Tarjan_num[i];
            Way[i] = 1;
            if (dis[ans] < dis[i])
                ans = i;
        }
    return;
}

void Topo(void)
{
    register int i, ID, To;
    while (!Q.empty())
    {
        ID = Q.front();
        Q.pop();
        for (i = head[ID]; i; i = Next[i])
        {
            To = to[i];
            --inDeg[To];
            if (dis[To] < dis[ID] + Tarjan_num[To])
            {
                dis[To] = dis[ID] + Tarjan_num[To];
                Way[To] = 0;
                if (dis[ans] < dis[To])
                    ans = To;
            }
            if (!inDeg[To])
                Q.push((int)To);
            if (dis[To] == dis[ID] + Tarjan_num[To])
                Way[To] = (Way[To] + Way[ID]) % x;
        }
    }
    return;
}

void Tarjan(int ID)
{
    register int i, To;
    vis[ID] = true;
    dfn[ID] = low[ID] = ++time;
    S.push(ID);
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
            To = S.top();
            S.pop();
            ++Tarjan_num[Tarjan_cnt];
            vis[To] = false;
            color[To] = Tarjan_cnt;
        } while (To != ID);
    }
    return;
}

void Add_Edge(int f, int t)
{
    Next[++cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt;
    return;
}

bool sort_rule(int a, int b)
{
    if (f[a] != f[b])
        return f[a] < f[b];
    else
        return t[a] < t[b];
}
