#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define MOD 999911658ll
const ll b[40]={2ll,3ll,4679ll,35617ll};

ll n,g,a[40];

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

ll fac[500000];

inline void Init(reg ll p){
	fac[0]=1;
	for(reg ll i=1;i<=p;++i)
		fac[i]=fac[i-1]*i%p;
	return;
}

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

inline ll C(reg ll n,reg ll m,reg ll mod){
	if(n<m)
		return 0;
	return fac[n]*inv(fac[n-m]*fac[m]%mod,mod)%mod;
}

inline ll Lucas(reg ll n,reg ll m,reg ll mod){
	if(n<m)
		return 0;
	if(!n)
		return 1;
	return Lucas(n/mod,m/mod,mod)*C(n%mod,m%mod,mod)%mod;
}

inline ll CRT(void){
	reg ll res=0;
	for(reg int i=0;i<4;++i)
		res=(res+a[i]*(MOD/b[i])%MOD*pow(MOD/b[i],b[i]-2,b[i]))%MOD;
	return res;
}

signed main(void){
	scanf("%lld%lld",&n,&g);
	if(g%(MOD+1)==0){
		puts("0");
		return 0;
	}
	for(reg int x=0;x<4;++x){
		Init(b[x]);
		for(reg ll i=1;i*i<=n;++i)
			if(n%i==0){
				a[x]=(a[x]+Lucas(n,i,b[x]))%b[x];
				if(i*i!=n)
					a[x]=(a[x]+Lucas(n,n/i,b[x]))%b[x];
			}
	}
	printf("%lld\n",pow(g,CRT(),MOD+1));
	return 0;
}