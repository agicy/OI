#include <cstdio>
#define MOD 1000000007
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline int read(void)
{
	register char ch = getchar();
	register int sum = 0;
	while (!(ch >= '0' && ch <= '9'))
		ch = getchar();
	while (ch >= '0' && ch <= '9')
		sum = (sum << 1) + (sum << 3) + ch - 48, ch = getchar();
	return sum;
}

int n, m, a[1001][1001], f[1001][1001];

int main(void)
{
	register int i, j, k, l;
	f[1][1] = 1;
	n = read(), m = read(), read();
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
		{
			a[i][j] = read();
			for (k = 1; k < i; ++k)
				for (l = 1; l < j; ++l)
					if (a[k][l] != a[i][j])
						f[i][j] = (f[i][j] + f[k][l]) % MOD;
		}
	printf("%d\n", f[n][m]);
	return 0;
}