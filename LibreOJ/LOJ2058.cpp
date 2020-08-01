#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXSIZE=MAXN<<2;

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	typedef vector<int> poly;
	poly r;
	inline int add(reg int a,reg int b){
		reg int sum=a+b;
		return sum>=p?sum-p:sum;
	}
	inline int sub(reg int a,reg int b){
		reg int res=a-b;
		return res<0?res+p:res;
	}
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
int fac[MAXN],inv[MAXN],invfac[MAXN];

int main(void){
	scanf("%d",&n);
	inv[1]=invfac[0]=fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=pow(fac[n],p-2,p);
	for(reg int i=n-1;i>=1;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	for(reg int i=2;i<=n;++i)
		inv[i]=1ll*(p-p/i)*inv[p%i]%p;
	a.resize(n+1),b.resize(n+1);
	a[0]=b[0]=1;
	a[1]=p-1,b[1]=n+1;
	for(reg int i=2;i<=n;++i){
		a[i]=i&1?(p-invfac[i]):invfac[i],
		b[i]=1ll*sub(pow(i,n+1,p),1)*inv[i-1]%p*invfac[i]%p;
	}
	poly t=mul(a,b);
	reg int p2=1;
	reg int ans=0;
	for(reg int i=0;i<=n;++i){
		ans=add(ans,1ll*p2*fac[i]%p*t[i]%p);
		p2=add(p2,p2);
	}
	printf("%d\n",ans);
	return 0;
}