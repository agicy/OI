#include <cstdio>
#define MOD 1000000007ll
typedef long long ll;

long long n, m, k, q, a[500001];

ll pow(ll x, ll exp, ll mod);
ll f(ll a[], ll x);
ll C(ll n, ll k);

int main(void)
{
    register int i;
    scanf("%lld%lld%lld%lld", &n, &m, &k, &q);
    for (i = 0; i <= m; ++i)
        scanf("%lld", &a[i]);
    printf("%lld\n", f(a, q % MOD) * C(n, k) % MOD);
    return 0;
}

ll pow(ll x, ll exp, ll mod)
{
    if (!exp)
        return 1;
    else if (exp == 1)
        return x;
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

ll C(ll n, ll k)
{
    register int i;
    register ll ans = 1, res = 1;
    for (i = n - k + 1; i <= n; ++i)
        ans = (ans * i) % MOD;
    for (i = 2; i <= k; ++i)
        res = (res * i) % MOD;
    return (ans * pow(res, MOD - 2, MOD)) % MOD;
}

ll f(ll a[], ll x)
{
    register int i;
    register ll ans = a[m] % MOD;
    for (i = m; i; --i)
        ans = ((ans * x) % MOD + a[i - 1]) % MOD;
    return ans;
}