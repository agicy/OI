#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, h[5001], dp[5001][5001];

bool watch(int l, int point, int r);

int main(void)
{
	register int i, j, ans = 0, sum, p;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
		scanf("%d", &h[i]);
	for (i = 1; i <= n; ++i)
	{
		ans ^= (sum = dp[i][i] = 1);
		p = 0;
		for (j = i - 1; j >= 1; --j)
		{
			if (!p || watch(j, p, i))
				sum += min(dp[j + 1][p - 1], dp[j + 1][p]), p = j;
			ans ^= (dp[j][i] = sum + min(dp[j][p - 1], dp[j][p]));
		}
	}
	printf("%d\n", ans);
	return 0;
}

bool watch(int l, int point, int r)
{
	return ((double)(h[point] - h[r]) / (point - r)) > ((double)(h[l] - h[r]) / (l - r));
}