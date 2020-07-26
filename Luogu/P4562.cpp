#include <cstdio>
#define MOD 1000000007ll
typedef long long ll;

bool vis[10000001];
ll l, r;

inline ll frac(ll n, ll mod);
inline ll inv(ll n, ll mod);
inline ll pow(ll x, ll exp, ll mod);

int main(void)
{
	register int i, j, sum = 0;
	scanf("%lld%lld", &l, &r);
	for (i = l; i <= r; ++i)
	{
		if (!vis[i])
		{
			++sum;
			for (j = (i << 1); j <= r; j += i)
				vis[j] = true;
		}
	}
	printf("%lld\n",
		   (
			   (
				   (
					   sum * frac(r - l + 2, MOD)) %
				   MOD) *
			   inv(sum + 1, MOD)) %
			   MOD);
	return 0;
}

inline ll frac(ll n, ll mod)
{
	register int i;
	register ll res = 1;
	for (i = 2; i <= n; ++i)
		res = (res * i) % mod;
	return res;
}

inline ll inv(ll n, ll mod)
{
	return pow(n, mod - 2, mod);
}

inline ll pow(ll x, ll exp, ll mod)
{
	register ll res = 1;
	while (exp)
	{
		if (exp & 1)
			res = res * x % MOD;
		exp >>= 1;
		x = (x * x) % mod;
	}
	return res;
}