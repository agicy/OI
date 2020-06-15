#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

ll n,a,c;

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll Exgcd(reg ll n,reg ll a,reg ll c){
	if(n==0||a==0)
		return 0;
	reg double k=1.0*a/c;
	reg ll K=k;
	if(k>=1)
		return (n*(n+1)/2%MOD*K%MOD+Exgcd(n,a-c*K,c))%MOD;
	else{
		reg ll N=(a*n/c)%MOD;
		reg ll res=(N*n%MOD-Exgcd(N,c,a)+MOD)%MOD;
		reg ll ext=N/(a/gcd(a,c))%MOD;
		return (res+ext)%MOD;
	}
}

int main(void){
	scanf("%lld%lld%lld",&n,&a,&c);
	printf("%lld\n",Exgcd(n,a,c));
	return 0;
}