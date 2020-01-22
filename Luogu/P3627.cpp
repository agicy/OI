#include <algorithm>
#include <cstdio>
#include <cstring>
using std::sort;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

bool vis[5000001];
int n, m, S, p, w[5000001], ATM[5000001];
int cnt, head[5000001], to[5000001], Next[5000001];
int time, dfn[5000001], low[5000001];
int Tarjan_cnt, color[5000001], wealth[5000001];
int Stack[5000001], top;
int Topo_d[5000001], inDeg[5000001];
int Q[5000001], _head, _tail;
int cnt_, head_[5000001], to_[5000001], Next_[5000001];

void Read(void);
void Tarjan(int);
void Rebuild(void);
void Topo(int);
void Write(void);
void Add_Edge(int, int);
void Add_Edge_(int, int);

int main(void)
{
    Read();
    Tarjan(S);
    Rebuild();
    Topo(S);
    Write();
    return 0;
}

void Read(void)
{
    register int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
    {
        static int f, t;
        scanf("%d%d", &f, &t);
        Add_Edge(f, t);
    }
    for (i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    scanf("%d%d", &S, &p);
    for (i = 1; i <= p; ++i)
        scanf("%d", &ATM[i]);
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

void Rebuild(void)
{
    register int i, j, To;
    for (i = 1; i <= n; ++i)
    {
        if (!dfn[i])
            continue;
        for (j = head[i]; j; j = Next[j])
        {
            To = to[j];
            if (color[i] != color[To])
            {
                ++inDeg[color[To]];
                Add_Edge_(color[i], color[To]);
            }
        }
    }
    return;
}

void Topo(int S)
{
    register int i, ID, To;
    Q[_tail++] = color[S];
    Topo_d[color[S]] = wealth[color[S]];
    while (_head < _tail)
    {
        ID = Q[_head++];
        for (i = head_[ID]; i; i = Next_[i])
        {
            To = to_[i];
            --inDeg[To];
            if (Topo_d[To] < Topo_d[ID] + wealth[To])
                Topo_d[To] = Topo_d[ID] + wealth[To];
            if (!inDeg[To])
                Q[_tail++] = To;
        }
    }
    return;
}

void Write(void)
{
    register int i, ans = 1;
    for (i = 1; i <= p; ++i)
        ans = max(ans, Topo_d[color[ATM[i]]]);
    printf("%d\n", ans);
    return;
}

void Add_Edge(int f, int t)
{
    Next[++cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt;
    return;
}

void Add_Edge_(int f, int t)
{
    Next_[++cnt] = head_[f];
    to_[cnt] = t;
    head_[f] = cnt;
    return;
}
