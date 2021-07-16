#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

int mod;

struct modInt{
	int x;
	inline modInt(void){return;}
	inline modInt(reg int x):x(x){return;}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res(1);
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

modInt inv2,inv6;

ll n;
int m;

const int MAXS=3e6+5;

bool vis[MAXS];
int tot,prime[MAXS];
modInt bas[MAXS];

inline void init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			bas[tot]=fpow(i%mod,m);
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

inline modInt sqr(const modInt& a){
	return a*a;
}

inline modInt calc(reg ll n){
	modInt tmp(n%mod);
	switch(m){
		case 1:return tmp*(tmp+1)*inv2;
		case 2:return tmp*(tmp+1)*(tmp*2+1)*inv6;
		case 3:return sqr(tmp*(tmp+1)*inv2);
		default:assert(false);
	}
}

ll ans;
__int128 epsilon=1;

inline void dfs(reg int las,reg ll x,const modInt& h){
	ans+=(h*calc(n/x)).x;
	if(ans>2305843009213693952) ans%=mod;

	for(reg int i=las+1;i<=tot&&epsilon*x*prime[i]*prime[i]<=n;++i){
		reg ll nx=x*prime[i]*prime[i];
		modInt nh=h*(bas[i]-bas[i]*bas[i]);
		for(reg int e=2;;++e){
			dfs(i,nx,nh);
			if(epsilon*nx*prime[i]>n)
				break;
			nx*=prime[i];
		}
	}
	return;
}

bool ed;
int main(void){
	scanf("%*d%lld%d%d",&n,&m,&mod);
	inv2=fpow(2,mod-2),inv6=fpow(6,mod-2);
	init(sqrt(n));
	dfs(0,1,1);
	printf("%lld\n",ans%mod);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}