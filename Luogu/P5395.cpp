#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;

namespace Poly{
	const int MAXSIZE=MAXN<<2;
	const int p=167772161;
	const int g=3;
	const int invg=55924054;
	typedef vector<int> poly;
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	int fac[MAXSIZE],invfac[MAXSIZE];
	inline void Poly_Init(reg int n){
		fac[0]=invfac[0]=1;
		for(reg int i=1;i<=n;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[n]=pow(fac[n],p-2,p);
		for(reg int i=n-1;i>=1;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		return;
	}
	vector<int> r;
	inline int Init(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		r.resize(limit);
		for(reg int i=1;i<limit;++i)
			r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg poly& a,reg int limit,reg int type){
		for(reg int i=0;i<limit;++i)
			if(i<r[i])
				swap(a[i],a[r[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
					a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
				}
			}
		}
		if(type==-1){
			reg int inv=pow(limit,p-2,p);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=Init(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
}

using namespace Poly;

int n;
poly a,b;

int main(void){
	scanf("%d",&n);
	Poly_Init(2e5);
	a.resize(n+1),b.resize(n+1);
	for(reg int i=0;i<=n;++i){
		a[i]=((i&1)?(p-1ll):1ll)*invfac[i]%p;
		b[i]=1ll*pow(i,n,p)*invfac[i]%p;
	}
	poly ans=mul(a,b);
	for(reg int i=0;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
