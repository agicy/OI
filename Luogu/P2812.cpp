#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int n, to[10001][10001], size[10001], temp, cnt, Edge[5000001][3], time, dfn[10001], low[10001], Tarjan_cnt, color[10001], Stack[10001], top, inDeg[10001], outDeg[10001];

void Tarjan(int);

int main(void)
{
    register int i, ans1 = 0, ans2 = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        do
            if (scanf("%d", &temp), temp == 0)
                break;
            else
                to[i][++size[i]] = temp,
                Edge[++cnt][1] = i,
                Edge[cnt][2] = temp;
        while (true);
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            Tarjan(i);
    for (i = 1; i <= cnt; ++i)
        if (color[Edge[i][1]] != color[Edge[i][2]])
            ++inDeg[color[Edge[i][2]]],
                ++outDeg[color[Edge[i][1]]];
    for (i = 1; i <= Tarjan_cnt; ++i)
    {
        if (!inDeg[i])
            ++ans1;
        if (!outDeg[i])
            ++ans2;
    }
    if (Tarjan_cnt == 1)
        puts("1\n0");
    else
        printf("%d\n%d\n", ans1, max(ans1, ans2));
    return 0;
}

void Tarjan(int ID)
{
    register int i, To;
    dfn[Stack[++top] = ID] = low[ID] = ++time;
    for (i = 1; i <= size[ID]; ++i)
        if (To = to[ID][i], !dfn[To])
            Tarjan(To), low[ID] = min(low[ID], low[To]);
        else if (!color[To])
            low[ID] = min(low[ID], dfn[To]);
        else
            continue;
    if (dfn[ID] == low[ID])
    {
        ++Tarjan_cnt;
        do
            color[To = Stack[top--]] = Tarjan_cnt;
        while (ID != To);
    }
    return;
}