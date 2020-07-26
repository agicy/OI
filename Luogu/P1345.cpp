#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using std::queue;
#define INF 0X3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))

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

const int MAXN = 100 + 5;
const int MAXM = 600 + 5;

struct Edge
{
	int Next, to, w;
};

int n, m, s, t, Maxflow, dep[MAXN << 1];
int cnt = -1, head[MAXN << 1], cur[MAXN << 1];
Edge E[(MAXN << 1) + (MAXM << 2)];
queue<int> Q;

void Add_Edge(int f, int t, int w, bool flag);
bool bfs(int s, int t);
int dfs(int now, int t, int limit);
void Dinic(int s, int t);

int main(void)
{
	register int i, u, v;
	memset(head, -1, sizeof(head));
	n = read(), m = read(), s = read(), t = read();
	for (i = 1; i <= n; ++i)
	{
		Add_Edge(i, i + n, 1, true);
		Add_Edge(i + n, i, 1, false);
	}
	for (i = 1; i <= m; ++i)
	{

		u = read(), v = read();
		Add_Edge(u + n, v, INF, true);
		Add_Edge(v, u + n, INF, false);
		Add_Edge(v + n, u, INF, true);
		Add_Edge(u, v + n, INF, false);
	}
	Dinic(s + n, t);
	printf("%d\n", Maxflow);
	return 0;
}

void Add_Edge(int f, int t, int w, bool flag)
{
	E[++cnt].Next = head[f];
	E[cnt].to = t;
	if (flag)
		E[cnt].w = w;
	head[f] = cnt;
	return;
}

bool bfs(int s, int t)
{
	register int i, now;
	memset(dep, 0X7F, sizeof(dep));
	memcpy(cur, head, sizeof(cur));
	dep[s] = 0;
	while (!Q.empty())
		Q.pop();
	Q.push(s);
	while (!Q.empty())
	{
		now = Q.front();
		Q.pop();
		for (i = head[now]; i != -1; i = E[i].Next)
		{
			if (dep[E[i].to] > INF && E[i].w)
			{
				dep[E[i].to] = dep[now] + 1;
				Q.push(E[i].to);
			}
		}
	}
	if (dep[t] < INF)
		return true;
	else
		return false;
}

int dfs(int now, int t, int limit)
{
	if (!limit || now == t)
		return limit;
	register int i, flow = 0, f;
	for (i = cur[now]; i != -1; i = E[i].Next)
	{
		cur[now] = i;
		if (dep[E[i].to] == dep[now] + 1 && (f = dfs(E[i].to, t, min(limit, E[i].w))))
		{
			flow += f;
			limit -= f;
			E[i].w -= f;
			E[i ^ 1].w += f;
			if (!limit)
				break;
		}
	}
	return flow;
}

void Dinic(int s, int t)
{
	while (bfs(s, t))
		Maxflow += dfs(s, t, INF);
	return;
}