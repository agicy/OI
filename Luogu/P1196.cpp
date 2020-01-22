#include <cstdio>
#include <iostream>
using std::cin;
#define abs(a) ((a) > 0 ? (a) : (-(a)))

int T, ID[30001], front[30001], num[30001];

int find(int);

int main(void)
{
    register int i;
    scanf("%d", &T);
    for (i = 1; i <= 30000; ++i)
    {
        ID[i] = i;
        num[i] = 1;
    }
    while (T--)
    {
        static char ch;
        static int x, y, fx, fy;
        cin >> ch;
        scanf("%d%d", &x, &y);
        fx = find(x), fy = find(y);
        if (ch == 'M')
        {
            front[fx] += num[fy];
            ID[fx] = fy;
            num[fy] += num[fx];
            num[fx] = 0;
        }
        else if (fx != fy)
            puts("-1");
        else
            printf("%d\n", abs(front[x] - front[y]) - 1);
    }
    return 0;
}

int find(int x)
{
    if (ID[x] == x)
        return ID[x];
    else
    {
        register int root = find(ID[x]);
        front[x] += front[ID[x]];
        return ID[x] = root;
    }
}