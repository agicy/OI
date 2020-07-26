#include <cstdio>
#include <cstring>
#include <queue>
using std::queue;
#define INF 0X3F3F3F3F

bool vis[100001];
int n, m;
int cnt, head[100001], to[200001], w[200001], Next[200001];
int dis[100001], inQue[100001];
int ans[100001];
int Stack[100001], top;
queue<int> Q;

void Add_Edge(int, int, int);
bool SPFA(int);

int main(void)
{
	register int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i)
	{
		static int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		Add_Edge(u, v, w);
		Add_Edge(v, u, w);
	}
	if (!SPFA(1) || dis[n] == INF)
		puts("-1");
	else
	{
		for (i = ans[n]; i; i = ans[i])
			Stack[++top] = i;
		while (top)
		{
			printf("%d ", Stack[top--]);
		}
		printf("%d\n", n);
	}
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

bool SPFA(int S)
{
	register int i, ID, To;
	memset(dis, 0X3F, sizeof(dis));
	vis[S] = true;
	dis[S] = 0;
	Q.push(S);
	while (!Q.empty())
	{
		ID = Q.front();
		Q.pop();
		vis[ID] = false;
		for (i = head[ID]; i; i = Next[i])
		{
			To = to[i];
			if (dis[To] > dis[ID] + w[i])
			{
				dis[To] = dis[ID] + w[i];
				ans[To] = ID;
				if (!vis[To])
				{
					vis[To] = true;
					Q.push((int)To);
					if (++inQue[To] > n)
						return false;
				}
			}
		}
	}
	return true;
}