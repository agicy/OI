#include <cstdio>

struct SegmentTree
{
	struct Node
	{
		int val;
	};
#define MAX_SIZE 100000
	Node unit[MAX_SIZE << 2];
#undef MAX_SIZE
	void Build(int ID, int l, int r, int num[]);
	void Update(int ID, int l, int r, int k);
	long long Query(int ID, int L, int R, int l, int r);
};

int list[100001];
int n, m;
SegmentTree T;

int main(void)
{
	register int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
		scanf("%d", &list[i]);
	T.Build(1, 1, n, list);
	scanf("%d", &m);
	while (m--)
	{
		static int opt, l, r, k;
		scanf("%d", &opt);
		if (opt == 1)
		{
			scanf("%d", &k);
			T.Update(1, 1, n, k);
		}
		else if (opt == 2)
		{
			scanf("%d%d", &l, &r);
			printf("%lld\n", T.Query(1, 1, n, l, r));
		}
	}
	return 0;
}

void SegmentTree::Build(int ID, int l, int r, int num[])
{
	if (l == r)
		unit[ID].val = num[l];
	else
	{
		register int mid = (l + r) >> 1;
		Build(ID << 1, l, mid, num);
		Build(ID << 1 | 1, mid + 1, r, num);
		unit[ID].val = unit[ID << 1].val + unit[ID << 1 | 1].val;
	}
	return;
}

void SegmentTree::Update(int ID, int l, int r, int k)
{
	if (l == r)
	{
		unit[ID].val = 1 - unit[ID].val;
	}
	else
	{
		register int mid = (l + r) >> 1;
		if (k <= mid)
			Update(ID << 1, l, mid, k);
		else
			Update(ID << 1 | 1, mid + 1, r, k);
		unit[ID].val = unit[ID << 1].val + unit[ID << 1 | 1].val;
	}
	return;
}

long long SegmentTree::Query(int ID, int L, int R, int l, int r)
{
	if (r < L || R < l)
		return 0;
	else if (L == R && l <= L && R <= r)
		return unit[ID].val == 0;
	else
	{
		register int mid = (L + R) >> 1;
		if (unit[ID].val % 2 == 0)
			return Query(ID << 1, L, mid, l, r) + Query(ID << 1 | 1, mid + 1, R, l, r) + 1;
		else
			return Query(ID << 1, L, mid, l, r) + Query(ID << 1 | 1, mid + 1, R, l, r);
	}
}
