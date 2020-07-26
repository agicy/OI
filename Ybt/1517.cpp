#include <cstdio>
#include <cstring>
#define INF 0X3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))

bool vis[3001];
int n, p, r;
int w[3001];
int cnt, head[3001], to[8001], Next[8001];
int time, dfn[3001], low[3001], Tarjan_cnt, color[3001];
int min_w[3001], inDeg[3001];
int Stack[3001], top;

void Add_Edge(int, int);
void Tarjan(int);

int main(void)
{
	register int i, j, To, sum = 0;
	memset(w, 0X3F, sizeof(w));
	scanf("%d%d", &n, &p);
	for (i = 1; i <= p; ++i)
	{
		static int id, money;
		scanf("%d%d", &id, &money);
		w[id] = money;
	}
	scanf("%d", &r);
	for (i = 1; i <= r; ++i)
	{
		static int a, b;
		scanf("%d%d", &a, &b);
		Add_Edge(a, b);
	}
	for (i = 1; i <= n; ++i)
		if (!dfn[i] && w[i] < INF)
			Tarjan(i);
	for (i = 1; i <= n; ++i)
		for (j = head[i]; j; j = Next[j])
		{
			To = to[j];
			if (color[i] != color[To])
				++inDeg[color[To]];
		}
	for (i = 1; i <= n; ++i)
		if (!dfn[i])
		{
			printf("NO\n%d\n", i);
			return 0;
		}
	puts("YES");
	for (i = 1; i <= Tarjan_cnt; ++i)
		if (!inDeg[i])
			sum += min_w[i];
	printf("%d\n", sum);
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
	register int i, To, Min = INF;
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
			Min = min(Min, w[To]);
		} while (To != ID);
		min_w[Tarjan_cnt] = Min;
	}
	return;
}
