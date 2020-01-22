#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline int read(void)
{
    register char ch = getchar();
    register int sum = 0;
    while (!(ch >= '0' && ch <= '9'))
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        sum = (sum << 1) + (sum << 3) + ch - 48, ch = getchar();
    return sum;
}

bool vis[100001];
int n;
int to[100001];
int time, dfn[100001], low[100001];
int Tarjan_cnt, color[100001], size[100001];
int top, Stack[100001];
int to_[100001];
int f[100001];

void Tarjan(int);
int DFS(int);

int main(void)
{
    register int i;
    n = read();
    for (i = 1; i <= n; ++i)
        to[i] = read();
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            Tarjan(i);
    for (i = 1; i <= n; ++i)
        if (color[i] != color[to[i]])
            to_[color[i]] = color[to[i]];
    for (i = 1; i <= n; ++i)
        printf("%d\n", DFS(color[i]));
    return 0;
}

void Tarjan(int ID)
{
    register int To;
    vis[ID] = true;
    dfn[ID] = low[ID] = ++time;
    Stack[++top] = ID;
    if (!dfn[to[ID]])
    {
        Tarjan(to[ID]);
        low[ID] = min(low[ID], low[to[ID]]);
    }
    else if (vis[to[ID]])
        low[ID] = min(low[ID], dfn[to[ID]]);
    if (dfn[ID] == low[ID])
    {
        ++Tarjan_cnt;
        do
        {
            To = Stack[top--];
            vis[To] = false;
            color[To] = Tarjan_cnt;
            ++size[color[To]];
        } while (To != ID);
    }
    return;
}

int DFS(int ID)
{
    if (f[ID])
        return f[ID];
    f[ID] = size[ID];
    if (to_[ID])
        f[ID] += DFS(to_[ID]);
    return f[ID];
}