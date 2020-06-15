#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

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

ll g,p;
map<ll,ll> M;
ll m;

inline void Init(void){
	M.clear();
	m=ceil(sqrt(p));
	ll pm=pow(g,m,p);
	reg ll mul=1;
	for(reg ll i=1;i<=m;++i){
		M[mul*pm%p]=i*m;
		mul=mul*pm%p;
	}
	return;
}

inline ll Solve(reg ll x){
	reg ll mul=1;
	for(reg ll i=0;i<=m;++i){
		if(M[mul*x%p]){
			return M[mul*x%p]-i;
		}
		mul=mul*g%p;
	}
	return -1;
}

ll n;

int main(void){
	scanf("%lld%lld",&g,&p);
	Init();
	scanf("%lld",&n);
	for(reg int i=1;i<=n;++i){
		static ll A,B;
		scanf("%lld%lld",&A,&B);
		reg int a=Solve(A);
		printf("%lld\n",pow(B,a,p));
	}
	return 0;
}