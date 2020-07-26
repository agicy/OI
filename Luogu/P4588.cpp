#include <cstdio>
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline long long read(void)
{
	register char ch = getchar();
	register long long sum = 0;
	while (!(ch >= '0' && ch <= '9'))
		ch = getchar();
	while (ch >= '0' && ch <= '9')
		sum = (sum << 1) + (sum << 3) + ch - '0', ch = getchar();
	return sum;
}

struct SegementTree
{
	struct Node
	{
		long long val;
	};
#define MAX_SIZE 100000
	Node unit[MAX_SIZE << 2];
#undef MAX_SIZE
	void Init(int ID, int L, int R);
	void Update(int ID, int L, int R, int k, long long val);
	long long Query(void);
};

long long T, Q, mod, opt, x;
SegementTree Tree;

int main(void)
{
	register int i;
	T = read();
	while (T--)
	{
		Q = read(), mod = read();
		Tree.Init(1, 1, Q);
		for (i = 1; i <= Q; ++i)
		{
			opt = read(), x = read() % mod;
			if (opt == 1)
				Tree.Update(1, 1, Q, i, x);
			else if (opt == 2)
				Tree.Update(1, 1, Q, x, 1);
			printf("%lld\n", Tree.Query());
		}
	}
	return 0;
}

void SegementTree::Init(int ID, int L, int R)
{
	unit[ID].val = 1;
	if (L == R)
		return;
	else
	{
		register int mid = (L + R) >> 1;
		Init(ID << 1, L, mid);
		Init(ID << 1 | 1, mid + 1, R);
	}
	return;
}

void SegementTree::Update(int ID, int L, int R, int k, long long val)
{
	if (L == k && k == R)
	{
		unit[ID].val = val;
	}
	else
	{
		register int mid = (L + R) >> 1;
		if (k <= mid)
			Update(ID << 1, L, mid, k, val);
		else
			Update(ID << 1 | 1, mid + 1, R, k, val);
		unit[ID].val = (unit[ID << 1].val * unit[ID << 1 | 1].val) % mod;
	}
	return;
}

long long SegementTree::Query(void)
{
	return unit[1].val;
}
