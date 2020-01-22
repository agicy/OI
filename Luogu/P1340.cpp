#include <algorithm>
#include <cstdio>
using std::sort;

struct Edge
{
    int ID, f, t, val;
    bool operator<(const Edge &a) const
    {
        return val < a.val;
    }
};

struct Union_Find
{
    int ID[201];
    Union_Find(int);
    void connect(int, int);
    bool search(int, int);
    int find(int);
};

int n, w;
Edge E[6001];

int Kruskal(int);

int main(void)
{
    register int i;
    scanf("%d%d", &n, &w);
    for (i = 1; i <= w; ++i)
    {
        E[i].ID = i;
        scanf("%d%d%d", &E[i].f, &E[i].t, &E[i].val);
    }
    sort(E + 1, E + w + 1);
    for (i = 1; i <= w; ++i)
    {
        printf("%d\n", Kruskal(i));
    }
    return 0;
}

Union_Find::Union_Find(int n)
{
    register int i;
    for (i = 1; i <= n; ++i)
        ID[i] = i;
    return;
}

void Union_Find::connect(int a, int b)
{
    register int ra = find(a), rb = find(b);
    if (ra != rb)
        ID[rb] = ra;
    return;
}

bool Union_Find::search(int a, int b)
{
    return find(a) == find(b);
}

int Union_Find::find(int x)
{
    if (x == ID[x])
        return x;
    else
        return ID[x] = find(ID[x]);
}

int Kruskal(int time)
{
    register int i, cnt = 0, sum = 0;
    Union_Find UF(n);
    for (i = 1; i <= w && cnt < n - 1; ++i)
        if (E[i].ID > time)
            continue;
        else if (!UF.search(E[i].f, E[i].t))
        {
            ++cnt;
            sum += E[i].val;
            UF.connect(E[i].f, E[i].t);
        }
    if (cnt != n - 1)
        return -1;
    else
        return sum;
}