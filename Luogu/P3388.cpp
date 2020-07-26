#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))

bool cut[20001];
int n, m, cnt, head[20001], to[200001], Next[200001];
int time, dfn[20001], low[20001];

void Add_Edge(int, int);
void Tarjan(int, int);

int main(void)
{
	register int i, ans = 0;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i)
	{
		static int x, y;
		scanf("%d%d", &x, &y);
		Add_Edge(x, y);
		Add_Edge(y, x);
	}
	for (i = 1; i <= n; ++i)
		if (!dfn[i])
			Tarjan(i, i);
	for (i = 1; i <= n; ++i)
		if (cut[i])
			++ans;
	printf("%d\n", ans);
	for (i = 1; i <= n; ++i)
		if (cut[i])
			printf("%d ", i);
	putchar('\n');
	return 0;
}

void Add_Edge(int f, int t)
{
	Next[++cnt] = head[f];
	to[cnt] = t;
	head[f] = cnt;
	return;
}

void Tarjan(int ID, int fa)
{
	register int i, To, child = 0;
	dfn[ID] = low[ID] = ++time;
	for (i = head[ID]; i; i = Next[i])
	{
		To = to[i];
		if (!dfn[To])
		{
			Tarjan(To, fa);
			low[ID] = min(low[ID], low[To]);
			if (low[To] >= dfn[ID] && ID != fa)
				cut[ID] = true;
			if (ID == fa)
				++child;
		}
		low[ID] = min(low[ID], dfn[To]);
	}
	if (child >= 2 && ID == fa)
		cut[ID] = true;
	return;
}