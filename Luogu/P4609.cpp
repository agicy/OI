#include <cstdio>
typedef long long ll;
#define MOD 1000000007LL
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

const int MAXN = 50000 + 5;
const int MAXAB = 100 + 5;

int T, n, A, B;
ll S[MAXN][MAXAB << 1], C[MAXAB << 1][MAXAB];

int main(void)
{
	register int i, j;
	S[0][0] = C[0][0] = 1;
	for (i = 1; i <= 50000; ++i)
		for (j = 1; j <= 200; ++j)
			S[i][j] = (S[i - 1][j - 1] + (S[i - 1][j] * (i - 1)) % MOD) % MOD;
	for (i = 1; i <= 200; ++i)
	{
		C[i][0] = 1;
		for (j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	T = read();
	while (T--)
	{
		n = read(), A = read(), B = read();
		printf("%lld\n", (S[n - 1][A + B - 2] * C[A + B - 2][A - 1]) % MOD);
	}
	return 0;
}