#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

inline ll bsgs(reg ll a,reg ll b,reg ll m){
	map<ll,int> M;
	reg int p=ceil(sqrt(m));
	reg ll x=1;
	M[1]=0;
	for(reg int i=1;i<=p;++i){
		x=mul(x,a,m);
		M[mul(x,b,m)]=i;
	}
	ll n=1;
	for(reg int i=1;i<=p;++i){
		n=mul(n,x,m);
		if(M.find(n)!=M.end())
			return 1ll*p*i-M[n];
	}
	return -1;
}

int main(void){
	ll k,m;
	scanf("%lld%lld",&k,&m);
	printf("%lld\n",bsgs(10,9*k+1,m));
	return 0;
}