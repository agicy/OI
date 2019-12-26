#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3Fll

ll l;

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=(res+a)%mod;
		a=(a<<1)%mod;
		b>>=1;
	}
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

inline ll phi(reg ll n){
	reg ll res=n;
	for(reg ll i=2;i*i<=n;++i)
		if(n%i==0){
			res=res/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	if(n>1)
		res=res/n*(n-1);
	return res;
}

int main(void){
	reg int cnt=0;
	while(scanf("%lld",&l)!=EOF&&l){
		reg ll mod=9ll*l/gcd(8ll,l),p=phi(mod),ans=INF;
		for(reg ll i=1;i*i<=p;++i)
			if(p%i==0){
				if(pow(10,i,mod)==1)
					ans=min((ll)ans,(ll)i);
				if(pow(10,p/i,mod)==1)
					ans=min((ll)ans,p/i);
			}
		printf("Case %d: %lld\n",++cnt,ans==INF?0:ans);
	}
	return 0;
}
