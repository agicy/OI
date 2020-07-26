#include <cstdio>
#define INF 0X3F3F3F3F3F3F3F3F
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef long long ll;

struct Segment_Tree //线段树模板
{
	ll unit[(200000 << 2) + 1];          //线段树空间要开到4倍
	void Update(int, int, int, int, ll); //更新函数
	ll Query(int, int, int, int, int);   //查询函数
};

char ch[2];
int m, len;
ll D, T, num;
Segment_Tree Tree; //线段树

int main(void)
{
	register int i;
	scanf("%d%lld", &m, &D);
	for (i = 1; i <= m; ++i)
	{
		scanf("%s%lld", ch, &num);
		if (ch[0] == 'Q')
		{
			if (!num)
				T = 0;
			else
				T = Tree.Query(1, 1, m, len - num + 1, len) % D;
			printf("%lld\n", T);
		}
		if (ch[0] == 'A')
		{
			++len;
			Tree.Update(1, 1, m, len, (num + T) % D);
		}
	}
	return 0;
}

void Segment_Tree::Update(int ID, int l, int r, int index, ll val)
{
	if (l == r)
		unit[ID] = val;
	else
	{
		register int mid = (l + r) >> 1;
		if (index <= mid)
			Update(ID << 1, l, mid, index, val); //更新左子树
		if (index > mid)
			Update(ID << 1 | 1, mid + 1, r, index, val); //更新右子树
		unit[ID] = max(unit[ID << 1], unit[ID << 1 | 1]) % D;
	}
	return;
}

ll Segment_Tree::Query(int ID, int l, int r, int x, int y)
{
	if (x <= l && r <= y)
		return unit[ID];
	register int mid = (l + r) >> 1;
	register ll a = -INF, b = -INF;
	if (x <= mid)
		a = Query(ID << 1, l, mid, x, y); //查询左子树
	if (y > mid)
		b = Query(ID << 1 | 1, mid + 1, r, x, y); //查询右子树
	return max(a, b); //返回查询结果
}
