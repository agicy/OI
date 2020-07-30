#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;

namespace Poly{
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
	inline poly inv(reg int deg,poly a){
		a.resize(deg);
		if(deg==1){
			poly res(1);
			res[0]=pow(a[0],p-2,p);
			return res;
		}
		poly b=inv((deg+1)>>1,a);
		reg int limit=Init(deg<<1);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			b[i]=1ll*(2ll-1ll*a[i]*b[i]%p+p)%p*b[i]%p;
		NTT(b,limit,-1);
		b.resize(deg);
		return b;
	}
}

using namespace Poly;

inline poly Solve(reg int l,reg int r){
	if(l==r){
		poly res(2);
		res[0]=1,res[1]=p-l;
		return res;
	}
	reg int mid=(l+r)>>1;
	return mul(Solve(l,mid),Solve(mid+1,r));
}

int n,k;
poly a,b;

int main(void){
	scanf("%d%d",&n,&k);
	if(n-k+1<=0){
		for(reg int i=0;i<=n;++i)
			printf("0%c",i==n?'\n':' ');
	}
	else{
		poly ans=Solve(1,k);
		ans=inv(n-k+1,ans);
		for(reg int i=0;i<k;++i)
			printf("0%c",i==n?'\n':' ');
		for(reg int i=k;i<=n;++i)
			printf("%d%c",ans[i-k],i==n?'\n':' ');
	}
	return 0;
}
