#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using std::less;
using std::priority_queue;
using std::sort;
using std::vector;
#define INF 0X3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

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

const int MAXN = 200000 + 5;
const int MAXM = 200000 + 5;

struct TreeArray
{
    int unit[MAXN];
    void Clear(void)
    {
        memset(unit, 0, sizeof(unit));
        return;
    }
    void Update(int a, int val, int n)
    {
        while (a <= n)
        {
            unit[a] += val;
            a += a & -a;
        }
        return;
    }
    int Query(int a)
    {
        register int sum = 0;
        while (a)
        {
            sum += unit[a];
            a -= a & -a;
        }
        return sum;
    }
};

struct Node
{
    int L, R;
    void Read(void)
    {
        L = read(), R = read();
        return;
    }
    bool operator<(const Node &a) const
    {
        return a.R > R;
    }
};

bool cmp(const Node &a, const Node &b)
{
    return a.L < b.L;
}

int T;
int n, m, k, a;
int A[MAXN];
Node S[MAXM];
TreeArray Tree;
priority_queue<Node, vector<Node>, less<Node> /* */> Q;

bool check(int mid);

int main(void)
{
    register int i, MAXA, MINA;
    T = read();
    while (T--)
    {
        MAXA = 0;
        MINA = INF;
        n = read(), m = read(), k = read(), a = read();
        for (i = 1; i <= n; ++i)
        {
            A[i] = read();
            MINA = min(MINA, A[i]);
            MAXA = max(MAXA, A[i]);
        }
        for (i = 1; i <= m; ++i)
            S[i].Read();
        sort(S + 1, S + m + 1, cmp);
        register int ans = -1, l = MINA, r = MAXA + MAXM * a, mid;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            if (check(mid))
            {
                ans = max(ans, mid);
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}

bool check(int mid)
{
    register int i, sum = 0, cur = 1;
    Node temp;
    Tree.Clear();
    for (i = 1; i <= n; ++i)
    {
        Tree.Update(i, A[i], n);
        Tree.Update(i + 1, -A[i], n);
    }
    while (!Q.empty())
        Q.pop();
    for (i = 1; i <= n; ++i)
    {
        while (cur <= m && S[cur].L <= i)
        {
            Q.push(S[cur]);
            ++cur;
        }
        while (Tree.Query(i) < mid)
        {
            if (Q.empty())
                return false;
            temp = Q.top();
            Q.pop();
            if (temp.R < i)
                return false;
            Tree.Update(temp.L, a, n);
            Tree.Update(temp.R + 1, -a, n);
            if (++sum > k)
                return false;
        }
    }
    return true;
}