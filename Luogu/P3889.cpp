#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using std::sort;

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

const int MAXN = 100000 + 5;
const int MAXM = 100000 + 5;
const int MAXA = 100000 + 5;
const int INIT = 100 + 1;

inline int max(int a, int b) { return a > b ? a : b; }

struct Node
{
	int ID, l, r;
	void Read(int i)
	{
		ID = i;
		l = read(), r = read();
		return;
	}
};

struct SegmentTree
{
	int unit[MAXN << 3];
	void Clear(void)
	{
		memset(unit, 0, sizeof(unit));
		return;
	}
	void Update(int ID, int l, int r, int x, int y)
	{
		if (l == r)
		{
			unit[ID] = max(unit[ID], y);
			return;
		}
		register int mid = (l + r) >> 1;
		if (x <= mid)
			Update(ID << 1, l, mid, x, y);
		if (x > mid)
			Update(ID << 1 | 1, mid + 1, r, x, y);
		unit[ID] = max(unit[ID << 1], unit[ID << 1 | 1]);
		return;
	}
	int Query(int ID, int l, int r, int x, int y)
	{
		if (l == x && r == y)
			return unit[ID];
		register int mid = (l + r) >> 1;
		if (y <= mid)
			return Query(ID << 1, l, mid, x, y);
		else if (x > mid)
			return Query(ID << 1 | 1, mid + 1, r, x, y);
		else
			return max(Query(ID << 1, l, mid, x, mid), Query(ID << 1 | 1, mid + 1, r, mid + 1, y));
	}
};

int n, m, a[MAXN], ans[MAXM];
int hash[MAXA];
int pre[2][MAXN][INIT], can[MAXN][INIT];
Node S[MAXM];
SegmentTree T;

bool cmp1(Node a, Node b);
bool cmp2(Node a, Node b);

int main(void)
{
	register int i, j, k, tot, last;
	n = read();
	for (i = 1; i <= n; ++i)
		a[i] = read();
	m = read();
	for (i = 1; i <= m; ++i)
		S[i].Read(i);
	for (i = 1; i <= n; ++i)
	{
		tot = 0;
		for (j = 1; j <= (int)sqrt(a[i]); ++j)
			if (a[i] % j == 0)
			{
				++tot;
				pre[0][i][tot] = hash[j];
				can[i][tot] = j;
				hash[j] = i;
				k = a[i] / j;
				if (j != k)
				{
					++tot;
					can[i][tot] = k;
					pre[0][i][tot] = hash[k];
					hash[k] = i;
				}
			}
		can[i][0] = tot;
	}
	memset(hash, 0, sizeof(hash));
	for (i = n; i >= 1; --i)
	{
		tot = 0;
		for (j = 1; j <= (int)sqrt(a[i]); ++j)
			if (a[i] % j == 0)
			{
				++tot;
				can[i][tot] = j;
				pre[1][i][tot] = hash[j];
				hash[j] = i;
				k = a[i] / j;
				if (k != j)
				{
					++tot;
					can[i][tot] = k;
					pre[1][i][tot] = hash[k];
					hash[k] = i;
				}
			}
		can[i][0] = tot;
	}
	last = 1;
	sort(S + 1, S + m + 1, cmp1);
	for (i = 1; i <= m; ++i)
	{
		for (j = last; j < S[i].l; ++j)
			for (k = 1; k <= can[j][0]; ++k)
				if (pre[1][j][k])
					T.Update(1, 1, n, pre[1][j][k], can[j][k]);
		ans[S[i].ID] = T.Query(1, 1, n, S[i].l, S[i].r);
		last = S[i].l;
	}
	last = n;
	T.Clear();
	sort(S + 1, S + m + 1, cmp2);
	for (i = 1; i <= m; ++i)
	{
		for (j = last; j > S[i].r; --j)
			for (k = 1; k <= can[j][0]; ++k)
				if (pre[0][j][k])
					T.Update(1, 1, n, pre[0][j][k], can[j][k]);
		ans[S[i].ID] = max(ans[S[i].ID], T.Query(1, 1, n, S[i].l, S[i].r));
		last = S[i].r;
	}
	for (i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}

bool cmp1(Node a, Node b)
{
	return a.l < b.l;
}

bool cmp2(Node a, Node b)
{
	return a.r > b.r;
}