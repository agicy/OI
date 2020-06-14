#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll MOD,n,inv6,inv2;

const int MAXSIZE=8000000+5;

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

int tot,prime[MAXSIZE];
ll phi[MAXSIZE];
ll Siphi[MAXSIZE];
bool vis[MAXSIZE];

inline void Init(reg int size){
	phi[1]=1;
	for(reg int i=2;i<=size;++i){
		if(!vis[i]){
			phi[i]=i-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=size;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j]%MOD;
				break;
			}
			phi[i*prime[j]]=phi[i]*phi[prime[j]]%MOD;
		}
	}
	for(reg int i=1;i<=size;++i)
		Siphi[i]=(Siphi[i-1]+phi[i]*i%MOD*i%MOD)%MOD;
	return;
}


inline ll Sum2(reg ll x){
	x=(x%MOD+MOD)%MOD;
	return x*(x+1)%MOD*inv2%MOD;
}

inline ll Sum3(reg ll x){
	x=(x%MOD+MOD)%MOD;
	return x*(x+1)%MOD*(2*x+1)%MOD*inv6%MOD;
}

inline ll sqr(reg ll x){
	return x*x%MOD;
}

int size;
map<ll,ll> M;

inline ll GetSiphi(ll x){
	if(x<=size)
		return Siphi[x];
	if(M[x])
		return M[x];
	reg ll res=sqr(Sum2(x));
	for(reg ll l=2,r;l<=x;l=r+1){
		r=x/(x/l);
		reg ll S=(Sum3(r)-Sum3(l-1)+MOD)%MOD;
		res=(res-GetSiphi(x/l)*S%MOD+MOD)%MOD;
	}
	return M[x]=res;
}

int main(void){
	scanf("%lld%lld",&MOD,&n);
	inv2=pow(2,MOD-2,MOD),inv6=pow(6,MOD-2,MOD);
	Init(size=min((ll)8e6,n));
	reg ll ans=0;
	for(reg ll l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans=(ans+sqr(Sum2(n/l))*((GetSiphi(r)-GetSiphi(l-1)+MOD)%MOD)%MOD)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}