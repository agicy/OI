#include <cstdio>
#include <map>
#include <queue>
#include <vector>
using std::greater;
using std::map;
using std::priority_queue;
using std::vector;
#define MOD 998244353LL
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef long long ll;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
static char buf[100000], *p1 = buf, *p2 = buf;

inline long long read(void)
{
	register char ch = getchar();
	register ll sum = 0;
	while (!(ch >= '0' && ch <= '9'))
		ch = getchar();
	while (ch >= '0' && ch <= '9')
		sum = sum * 10 + ch - 48, ch = getchar();
	return sum;
}

ll T, n, m, l, r, temp, cm;

ll f[102000000];
priority_queue<ll, vector<ll>, greater<ll> /**/> Q;
map<ll, ll> M;

inline ll pow(ll x, ll exp, ll mod);
inline ll inv(ll n, ll mod);
inline ll frac(ll n, ll mod);

int main(void)
{
	T = read();
	while (T--)
	{
		register ll i, top1 = 0, top2 = 0,min_a=1000000001, max_a = 0, res = 1;
		while (!Q.empty())
			Q.pop();
		M.clear();
		n = read(), m = read(), l = read(), r = read();
		cm = m;
		for (i = 1; i <= n; ++i)
		{
			temp = read();
			++M[temp];
			min_a = min(min_a, temp);
			max_a = max(max_a, temp);
		}
		for (i = l; i <= r; ++i)
			Q.push(M[i]), M[i] = 0;
		if (l == r)
		{
			Q.push(Q.top() + m);
			Q.pop();
		}
		else
		{
			while (m)
			{
				top1 = Q.top(), Q.pop();
				top2 = Q.top(), Q.pop();
				if (top1 == top2)
				{
					--m;
					Q.push(top1), Q.push(top2 + 1);
				}
				else
				{
					if (top2 - top1 <= m)
					{
						m -= top2 - top1;
						Q.push(top2), Q.push(top2);
					}
					else
					{
						Q.push(top1 + m), Q.push(top2);
						m = 0;
					}
				}
			}
		}
		for (i = min_a; i <= max_a; ++i)
			if (M[i])
				res = (res * frac(M[i], MOD)) % MOD;
		while (!Q.empty())
		{
			top1 = Q.top();
			Q.pop();
			res = (res * frac(top1, MOD)) % MOD;
		}
		printf("%lld\n", (frac(n + cm, MOD) * inv(res, MOD)) % MOD);
	}
	return 0;
}

inline ll frac(ll n, ll mod)
{
	if (f[n])
		return f[n];
	register ll i, res = 1;
	for (i = 2; i <= n; ++i)
		res = (res * i) % mod;
	return f[n] = res;
}

inline ll inv(ll n, ll mod)
{
	return pow(n, mod - 2, mod);
}

inline ll pow(ll x, ll exp, ll mod)
{
	if (!exp)
		return 1;
	else if (exp == 1)
		return x % mod;
	else if (exp & 1)
	{
		ll temp = pow(x, exp >> 1, mod);
		return (((temp * temp) % mod) * x) % mod;
	}
	else
	{
		ll temp = pow(x, exp >> 1, mod);
		return (temp * temp) % mod;
	}
}