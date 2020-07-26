#include <cstdio>
#define max(a, b) ((a) > (b) ? (a) : (b))

int n, R, x, y, v;
int sum[5002][5002];

int main(void)
{
	register int i, j, Max = 0;
	scanf("%d%d", &n, &R);
	for (i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", &x, &y, &v);
		sum[x + 1][y + 1] += v;
	}
	for (i = 1; i <= 5001; ++i)
		for (j = 1; j <= 5001; ++j)
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	for (i = R; i <= 5001; ++i)
		for (j = R; j <= 5001; ++j)
			Max = max(Max, sum[i][j] - sum[i - R][j] - sum[i][j - R] + sum[i - R][j - R]);
	printf("%d\n", Max);
	return 0;
}