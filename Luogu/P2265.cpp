#include <cstdio>
#define MOD 1000000007

typedef long long ll;

ll pow(ll, ll, ll);
ll inv(ll, ll);
ll frac(ll, ll);
ll C(ll, ll, ll);

ll n, m;

int main(void)
{
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", C(n, n + m, MOD));
    return 0;
}

ll pow(ll x, ll exp, ll mod){
    if(!exp)
        return 1;
    else if(exp==1)
        return x;
    else if(exp&1){
        long long temp = pow(x, exp >> 1, mod);
        return (((temp * temp) % mod) * x) % mod;
    }
    else{
        long long temp = pow(x, exp >> 1, mod);
        return (temp * temp) % mod;
    }
}

ll inv(ll x, ll p){
    return pow(x, p - 2, p) % p;
}

ll frac(ll x, ll mod){
    register ll i,res=1;
    for (i = 2; i <= x;++i)
        res = (res * i) % mod;
    return res;
}

ll C(ll n, ll m, ll mod){
    register ll a = frac(m, mod);
    register ll b = (inv(frac(n, mod), mod) * inv(frac(m - n, mod), mod)) % mod;
    return (a * b) % mod;
}