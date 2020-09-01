#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int p=1e9+7;

inline ll pow(ll x,ll exp,ll mod){
	ll res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

ll w,n,k;

int main(void){
	scanf("%lld%lld%lld",&w,&n,&k);
	printf("%lld\n",1ll*w*pow(pow(2,k,p),p-2,p)%p);
	return 0;
}