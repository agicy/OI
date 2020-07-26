#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::greater;
using std::priority_queue;
using std::vector;

const int MAXN = 500 + 5;
const int MAXM = 500 + 5;
const int fx[4] = {-1, 0, 0, 1}, fy[4] = {0, -1, 1, 0};

struct Node
{
	int x, y, t;
	Node(void)
	{
		return;
	}
	Node(int a, int b, int c)
	{
		x = a;
		y = b;
		t = c;
		return;
	}
};

bool vis[MAXN][MAXM];
char map[MAXN][MAXM];
int n, m;
int sx, sy, ex, ey;
Node temp;
priority_queue<Node, vector<Node>, greater<Node> /**/> Q;

void BFS(void);
bool operator>(Node a, Node b);

int main(void)
{
	register int i, j;
	while (scanf("%d%d", &n, &m) != EOF && n && m)
	{
		memset(vis, false, sizeof(vis));
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= m; ++j)
				cin >> map[i][j];
		scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
		sx += 1, sy += 1, ex += 1, ey += 1;
		while (!Q.empty())
			Q.pop();
		temp = Node(sx, sy, 0);
		Q.push(temp);
		BFS();
	}
	return 0;
}

void BFS(void)
{
	register int i, x, y, t, dx, dy;
	while (!Q.empty())
	{
		temp = Q.top();
		Q.pop();
		x = temp.x, y = temp.y, t = temp.t;
		if (x == ex && y == ey)
		{
			printf("%d\n", t);
			return;
		}
		if (vis[x][y])
			continue;
		vis[x][y] = true;
		for (i = 0; i < 4; ++i)
		{
			dx = x + fx[i], dy = y + fy[i];
			if (dx < 1 || n < dx || dy < 1 || m < dy || vis[dx][dy])
				continue;
			if (map[dx][dy] != map[x][y])
			{
				temp = Node(dx, dy, t + 1);
				Q.push(temp);
			}
			else
			{
				temp = Node(dx, dy, t);
				Q.push(temp);
			}
		}
	}
	return;
}

bool operator>(Node a, Node b)
{
	return a.t > b.t;
}
