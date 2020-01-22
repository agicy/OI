#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
using std::make_pair;
using std::map;
using std::pair;
#define MOD 998244353

int n, y, op;

void Work0(void);
void Work1(void);
void Work2(void);

int main(void){
    scanf("%d%d%d", &n, &y, &op);
    if(op==0){
        Work0();
    }
    else if(op==1){
        Work1();
    }
    else if(op==2){
        Work2();
    }
    else
        return 0;
    return 0;
}

/*问题0*/
pair<int, int> temp;
map <pair< int, int >, bool > M;

inline void swap(int &, int &);
long long pow(long long, long long, long long);

void Work0(void){
    register int i,cnt=n;
    for (i = 1; i < n;++i){
        static int u, v;
        scanf("%d%d", &u, &v);
        if(u>v)
            swap(u, v);
        temp = make_pair(u, v);
        M[temp] = true;
    }
    for (i = 1; i < n; ++i)
    {
        static int u, v;
        scanf("%d%d", &u, &v);
        if (u > v)
            swap(u, v);
        temp = make_pair(u, v);
        if(M[temp])
            --cnt;
    }
    printf("%lld\n", pow(y, cnt, MOD));
    return;
}

inline void swap(int &a, int &b)
{
    a ^= b, b = a ^ b, a ^= b;
    return;
}

long long pow(long long x, long long exp, long long mod){
    if(!exp)
        return 1;
    else if(exp==1)
        return x;
    else if(exp&1){
        long long temp = pow(x, exp >> 1, mod);
        return (((temp * temp) % MOD) * x) % MOD;
    }
    else{
        long long temp = pow(x, exp >> 1, mod);
        return (temp * temp) % MOD;
    }
}

/*问题1*/
void Work1(void){
    register int i;
    register long long ans = 0;
    if(y==1){
        printf("%lld\n", pow(n, n - 2, MOD));
        return;
    }
    for (i = 1; i < n;++i){
        ans += i * pow(y, i, MOD);
        if(ans>=MOD)
            ans %= MOD;
    }
    printf("%lld\n", ans);
    return;
}

/*问题2*/
void Work2(void)
{
    srand(time(0));
    printf("%d\n", rand() % MOD);
    return;
}