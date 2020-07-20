#include <cstdio>
#define INF 0X3F3F3F3F3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))

bool isNotPrime[100004];
int n, m, a[501][501];

int main(void)
{
	register int i, j;
	register long long now, temp, ans = INF;
	scanf("%d%d", &n, &m);
	isNotPrime[1] = true;
	for (i = 2; i <= 100003; ++i) {
		if (!isNotPrime[i])
			for (j = (i << 1); j <= 100003; j += i)
				isNotPrime[j] = true;
	}
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
			now = temp = a[i][j];
			while (isNotPrime[now])
				++now;
			a[i][j] = now - temp;
			a[i][0] += a[i][j];
			a[0][j] += a[i][j];
		}
	for (i = 1; i <= n; ++i)
		ans = min(ans, a[i][0]);
	for (j = 1; j <= m; ++j)
		ans = min(ans, a[0][j]);
	printf("%lld\n", ans);
	return 0;
}