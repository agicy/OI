#include <bits/stdc++.h>
using namespace std;

int T, n, m, a[30000 + 5], i, j, x, lastx, k;

int main(void)
{
	for (scanf("%d", &T), k = 1; k <= T; ++k)
	{
		priority_queue<int> Q1;
		priority_queue<int, vector<int>, greater<int> /**/> Q2;
		for (scanf("%d%d", &n, &m), i = 1; i <= n; scanf("%d", &a[i++]))
			;
		for (i = 1, j, x, lastx = 0; i <= m; ++i, printf("%d\n", Q2.top()), lastx = x, Q1.push(Q2.top()), Q2.pop())
			for (scanf("%d", &x), j = lastx + 1; j <= x; ++j)
				(Q2.push(a[j]), (!Q1.empty() && Q1.top() > Q2.top())) ? (Q2.push(Q1.top()), Q1.pop(), Q1.push(Q2.top()), Q2.pop(), 0) : (0);
		if (k < T)
			puts("");
	}
	return 0;
}