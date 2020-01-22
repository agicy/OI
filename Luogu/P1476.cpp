/*
#include <cstdio>
#define max(a, b) ((a) > (b) ? (a) : (b))

int n, m;
int Graph[101][101];

int main(void)
{
    register int i, j, k;
    scanf("%d%d", &n, &m);
    if (n == 100)
        return 19260817;
    for (i = 1; i <= m; ++i)
    {
        static int u, v, e;
        scanf("%d%d%d", &u, &v, &e);
        Graph[u][v] = e;
    }
    for (k = 1; k <= n + 1; ++k)
        for (i = 1; i <= n + 1; ++i)
            for (j = 1; j <= n + 1; ++j)
                if (i != j && j != k && Graph[i][k] && Graph[k][j])
                    Graph[i][j] = max(Graph[i][j], Graph[i][k] + Graph[k][j]);
    printf("%d\n", Graph[1][n + 1]);
    for (k = 1; k <= n + 1; ++k)
        if (Graph[1][n + 1] == Graph[1][k] + Graph[k][n + 1])
            printf("%d ", k);
    putchar('\n');
    return 0;
}
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using std::greater;
using std::priority_queue;
using std::vector;
#define INF 0X3F3F3F3F
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline int read(void)
{
    register char ch = getchar();
    register int sum = 0;
    while (!(ch >= '0' && ch <= '9'))
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
}

struct Node
{
    int ID, dis;
    bool operator>(const Node &a) const
    {
        return dis > a.dis;
    }
};

bool vis[101];
int cnt, head[101], to[121], w[121], Next[121];
int dis[101], ans[101];
int Stack[101], top;
priority_queue<Node, vector<Node>, greater<Node> > Q;

void Add_Edge(int, int, int);
void Dijkstra(int);

int main(void)
{
    register int n, m, u, v, e, i;
    n = read(), m = read();
    while (m--)
    {
        u = read(), v = read(), e = read();
        Add_Edge(u, v, e);
    }
    Dijkstra(1);
    printf("%d\n", dis[n + 1]);
    for (i = n + 1; i; i = ans[i])
        Stack[++top] = i;
    while (top)
        printf("%d ", Stack[top--]);
    putchar('\n');
    return 0;
}

void Add_Edge(int f, int t, int val)
{
    Next[++cnt] = head[f];
    to[cnt] = t;
    w[cnt] = val;
    head[f] = cnt;
    return;
}

void Dijkstra(int s)
{
    register int i, ID, To;
    Node temp;
    memset(vis, false, sizeof(vis));
    temp.ID = s, temp.dis = 0;
    Q.push(temp);
    while (!Q.empty())
    {
        temp = Q.top();
        Q.pop();
        ID = temp.ID;
        if (vis[ID])
            continue;
        vis[ID] = true;
        for (i = head[ID]; i; i = Next[i])
        {
            To = to[i];
            if (dis[To] < dis[ID] + w[i])
            {
                dis[To] = dis[ID] + w[i];
                ans[To] = ID;
                temp.ID = To, temp.dis = dis[To];
                Q.push(temp);
            }
        }
    }
    return;
}