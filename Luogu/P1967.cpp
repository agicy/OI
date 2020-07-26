#include <algorithm>
#include <cstdio>
using std::sort;
#define INF 0X3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))

struct Tree
{
	bool vis[10001];
	int cnt, head[10001], to[20001], w[20001], Next[20001];
	int dep[10001], fa[10001][21], W[10001][21];
	void DFS(int);
	void Add_Edge(int, int, int);
	void LCA_Init(void);
	int LCA(int, int);
};

struct Graph
{
	struct Kruskal
	{
		struct Edge
		{
			int f, t, val;
			bool operator<(const Edge &a) const
			{
				return val > a.val;
			}
		};

		struct Union_Find
		{
			int ID[10001];

			void Init(void);
			void connect(int, int);
			bool search(int, int);
			int find(int);
		};

		Union_Find B;
		Edge E[50001];

		void kruskal(void);
	};

	int n, m;
	Kruskal K;

	void Read(void);
};

int q;
Tree T;
Graph G;

int main(void)
{
	G.Read();
	G.K.B.Init();
	G.K.kruskal();
	T.LCA_Init();
	scanf("%d", &q);
	while (q--)
	{
		static int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", T.LCA(x, y));
	}

	return 0;
}

void Tree::Add_Edge(int f, int t, int val)
{
	Next[++cnt] = head[f];
	to[cnt] = t;
	w[cnt] = val;
	head[f] = cnt;
	return;
}

void Tree::DFS(int ID)
{
	register int i, To;
	vis[ID] = true;
	for (i = head[ID]; i; i = Next[i])
	{
		To = to[i];
		if (vis[To])
			continue;
		dep[To] = dep[ID] + 1;
		fa[To][0] = ID;
		W[To][0] = w[i];
		DFS(To);
	}
	return;
}

void Tree::LCA_Init(void)
{
	register int i, j;
	for (i = 1; i <= G.n; ++i)
		if (!vis[i])
		{
			dep[i] = 1;
			DFS(i);
			fa[i][0] = i;
			W[i][0] = INF;
		}
	for (i = 1; i <= 20; ++i)
		for (j = 1; j <= G.n; ++j)
		{
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
			W[j][i] = min(W[j][i - 1], W[fa[j][i - 1]][i - 1]);
		}
	return;
}

int Tree::LCA(int x, int y)
{
	if (!G.K.B.search(x, y))
		return -1;
	register int i, ans = INF;
	if (dep[x] > dep[y])
	{
		int temp = x;
		x = y;
		y = temp;
	}
	for (i = 20; i >= 0; --i)
		if (dep[fa[y][i]] >= dep[x])
		{
			ans = min(ans, W[y][i]);
			y = fa[y][i];
		}
	if (x == y)
		return ans;
	for (i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i])
		{
			ans = min(ans, min(W[x][i], W[y][i]));
			x = fa[x][i];
			y = fa[y][i];
		}
	ans = min(ans, min(W[x][0], W[y][0]));
	return ans;
}

void Graph::Kruskal::Union_Find::Init(void)
{
	register int i;
	for (i = 1; i <= G.n; ++i)
		ID[i] = i;
	return;
}

void Graph::Kruskal::Union_Find::connect(int a, int b)
{
	register int ra = find(a), rb = find(b);
	if (ra != rb)
		ID[rb] = ra;
	return;
}

bool Graph::Kruskal::Union_Find::search(int a, int b)
{
	return find(a) == find(b);
}

int Graph::Kruskal::Union_Find::find(int x)
{
	if (x == ID[x])
		return x;
	else
		return ID[x] = find(ID[x]);
}

void Graph::Kruskal::kruskal(void)
{
	register int i, cnt = 0;
	sort(E + 1, E + G.m + 1);
	for (i = 1; i <= G.m && cnt < G.n - 1; ++i)
	{
		if (!B.search(E[i].f, E[i].t))
		{
			B.connect(E[i].f, E[i].t);
			++cnt;
			T.Add_Edge(E[i].f, E[i].t, E[i].val);
			T.Add_Edge(E[i].t, E[i].f, E[i].val);
		}
	}
	return;
}

void Graph::Read(void)
{
	register int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i)
		scanf("%d%d%d", &K.E[i].f, &K.E[i].t, &K.E[i].val);
	return;
}