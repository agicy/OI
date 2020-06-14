#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353

ll l,r;

inline ll Calc(reg ll x){
	reg ll res=0;
	for(reg ll i=1,r;i<=x;i=r+1){
		r=x/(x/i);
		res=(res+(r-i+1)*(x/i)%MOD)%MOD;
	}
	return res;
}

int main(void){
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",(Calc(r)-Calc(l-1)+MOD)%MOD);
	return 0;
}