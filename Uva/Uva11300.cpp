#include <algorithm>
#include <cstdio>
#include <cstring>
using std::nth_element;
#define abs(a) ((a) > 0 ? (a) : (-(a)))

const int MAXN = 1000000 + 5;

int n;
long long a[MAXN], s[MAXN];

int main(void)
{
	register int i;
	register long long sum, ans, mid;
	while (scanf("%d", &n) != EOF)
	{
		sum = ans = 0;
		for (i = 1; i <= n; i++)
		{
			scanf("%lld", &a[i]);
			sum += a[i];
		}
		sum /= n;
		for (i = 1; i <= n; i++)
			s[i] = s[i - 1] + a[i] - sum;
		nth_element(s + 1, s + ((n + 1) >> 1), s + n + 1);
		mid = s[(n + 1) >> 1];
		for (i = 1; i <= n; i++)
			ans += abs(s[i] - mid);
		printf("%lld\n", ans);
	}
	return 0;
}