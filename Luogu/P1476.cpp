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