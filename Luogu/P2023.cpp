#include <cstdio>



struct SegmentTree
{
    struct Node
    {
        long long val, add, mul;
    };
#define Max_Size (100000 << 2)
    Node unit[Max_Size];
#undef Max_Size
    void Build(int ID, int l, int r, long long num[]);
    void pushdown(int ID, int l, int r);
    void Update_Add(int ID, int L, int R, int l, int r, long long k);
    void Update_Mul(int ID, int L, int R, int l, int r, long long k);
    long long Query(int ID, int L, int R, int l, int r);
};

int n, m;
long long p, a[100001];
SegmentTree T;

int main(void)
{
    register int i, opt, x, y;
    register long long k, ans;
    n = read(), p = read();
    for (i = 1; i <= n; ++i)
        a[i] = read();
    T.Build(1, 1, n, a);
    m = read();
    for (i = 1; i <= m; ++i)
    {
        opt = read();
        if (opt == 1)
        {
            x = read(), y = read(), k = read();
            T.Update_Mul(1, 1, n, x, y, k);
        }
        else if (opt == 2)
        {
            x = read(), y = read(), k = read();
            T.Update_Add(1, 1, n, x, y, k);
        }
        else if (opt == 3)
        {
            x = read(), y = read();
            ans = T.Query(1, 1, n, x, y);
            printf("%lld\n", ans);
        }
    }
    return 0;
}

void SegmentTree::Build(int ID, int l, int r, long long num[])
{
    unit[ID].mul = 1;
    unit[ID].add = 0;
    if (l == r)
    {
        unit[ID].val = num[l];
    }
    else
    {
        Build(ID << 1, l, (l + r) >> 1, num);
        Build(ID << 1 | 1, ((l + r) >> 1) + 1, r, num);
        unit[ID].val = unit[ID << 1].val + unit[ID << 1 | 1].val;
    }
    unit[ID].val %= p;
    return;
}

void SegmentTree::pushdown(int ID, int l, int r)
{
    register int mid = (l + r) >> 1;
    unit[ID << 1].val = (unit[ID << 1].val * unit[ID].mul + unit[ID].add * (mid - l + 1)) % p;
    unit[ID << 1 | 1].val = (unit[ID << 1 | 1].val * unit[ID].mul + unit[ID].add * (r - mid)) % p;
    unit[ID << 1].mul = (unit[ID << 1].mul * unit[ID].mul) % p;
    unit[ID << 1 | 1].mul = (unit[ID << 1 | 1].mul * unit[ID].mul) % p;
    unit[ID << 1].add = (unit[ID << 1].add * unit[ID].mul + unit[ID].add) % p;
    unit[ID << 1 | 1].add = (unit[ID << 1 | 1].add * unit[ID].mul + unit[ID].add) % p;
    unit[ID].mul = 1;
    unit[ID].add = 0;
    return;
}

void SegmentTree::Update_Mul(int ID, int L, int R, int l, int r, long long k)
{
    if (r < L || R < l)
        return;
    else if (l <= L && R <= r)
    {
        unit[ID].val = (unit[ID].val * k) % p;
        unit[ID].mul = (unit[ID].mul * k) % p;
        unit[ID].add = (unit[ID].add * k) % p;
    }
    else
    {
        pushdown(ID, L, R);
        Update_Mul(ID << 1, L, (L + R) >> 1, l, r, k);
        Update_Mul(ID << 1 | 1, ((L + R) >> 1) + 1, R, l, r, k);
        unit[ID].val = (unit[ID << 1].val + unit[ID << 1 | 1].val) % p;
    }
    return;
}

void SegmentTree::Update_Add(int ID, int L, int R, int l, int r, long long k)
{
    if (r < L || R < l)
        return;
    else if (l <= L && R <= r)
    {
        unit[ID].add = (unit[ID].add + k) % p;
        unit[ID].val = (unit[ID].val + k * (R - L + 1)) % p;
    }
    else
    {
        pushdown(ID, L, R);
        Update_Add(ID << 1, L, (L + R) >> 1, l, r, k);
        Update_Add(ID << 1 | 1, ((L + R) >> 1) + 1, R, l, r, k);
        unit[ID].val = (unit[ID << 1].val + unit[ID << 1 | 1].val) % p;
    }
    return;
}

long long SegmentTree::Query(int ID, int L, int R, int l, int r)
{
    if (r < L || R < l)
    {
        return 0;
    }
    else if (l <= L && R <= r)
    {
        return unit[ID].val;
    }
    else
    {
        pushdown(ID, L, R);
        return (Query(ID << 1, L, (L + R) >> 1, l, r) + Query(ID << 1 | 1, ((L + R) >> 1) + 1, R, l, r)) % p;
    }
}
