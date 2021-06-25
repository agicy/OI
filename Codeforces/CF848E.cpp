#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
		return;
	}
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
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

namespace Poly{
	const modInt g=3;
	const modInt invg=332748118;
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		if(rev.size()!=(unsigned)limit){
			rev.resize(limit);
			for(reg int i=0;i<limit;++i)
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		}
		return limit;
	}
	typedef vector<modInt> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			modInt w(fpow(flag==1?g:invg,(mod-1)/(i<<1)));
			for(reg int j=0;j<limit;j+=(i<<1)){
				modInt e(1);
				for(reg int k=0;k<i;++k,e*=w){
					modInt x(a[j+k]),y(e*a[i+j+k]);
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1){
			modInt inv=fpow(limit,mod-2);
			for(reg int i=0;i<limit;++i)
				a[i]*=inv;
		}
		return;
	}
	inline poly add(poly a,poly b){
		a.resize(max(a.size(),b.size()));
		for(reg int i=0,siz=b.size();i<siz;++i)
			a[i]+=b[i];
		return a;
	}
}

const int MAXN=5e4+5;

using Poly::NTT;
using Poly::poly;

int n;
modInt g[MAXN];
poly g0,g1,g2;
poly f0,f1,f2;

inline void solve(reg int l,reg int r){
	if(l==r){
		f0[l]+=g0[l],f1[l]+=g1[l],f2[l]+=g2[l];
		return;
	}
	reg int mid=(l+r)>>1;
	solve(l,mid);
	reg int limit=Poly::getRev(mid-l+1+r-l);
	poly tmpf0(limit),tmpf1(limit),tmpf2(limit);
	poly tmpg0(limit),tmpg1(limit),tmpg2(limit);
	for(reg int i=l;i<=mid;++i)
		tmpf0[i-l]=f0[i],tmpf1[i-l]=f1[i],tmpf2[i-l]=f2[i];
	NTT(tmpf0,limit,1),NTT(tmpf1,limit,1),NTT(tmpf2,limit,1);
	for(reg int i=0;i<=r-l;++i)
		tmpg0[i]=g0[i],tmpg1[i]=g1[i],tmpg2[i]=g2[i];
	NTT(tmpg0,limit,1),NTT(tmpg1,limit,1),NTT(tmpg2,limit,1);
	poly f0g0(limit),f1g1(limit),f0g1(limit),f1g2(limit),f2g2(limit);
	for(reg int i=0;i<limit;++i)
		f0g0[i]=tmpf0[i]*tmpg0[i],f1g1[i]=tmpf1[i]*tmpg1[i],f0g1[i]=tmpf0[i]*tmpg1[i],f1g2[i]=tmpf1[i]*tmpg2[i],f2g2[i]=tmpf2[i]*tmpg2[i];
	NTT(f0g0,limit,-1),NTT(f1g1,limit,-1),NTT(f0g1,limit,-1),NTT(f1g2,limit,-1),NTT(f2g2,limit,-1);
	for(reg int i=mid+1;i<=r;++i)
		f0[i]+=f0g0[i-l]+f1g1[i-l],f1[i]+=f0g1[i-l]+f1g2[i-l],f2[i]+=f1g1[i-l]+f2g2[i-l];
	solve(mid+1,r);
	return;
}

int main(void){
	scanf("%d",&n);
	g[0]=g[2]=1;
	for(reg int i=4;i<=n;i+=2)
		g[i]=g[i-2]+g[i-4];
	g0.resize(n+1),g1.resize(n+1),g2.resize(n+1);
	f0.resize(n+1),f1.resize(n+1),f2.resize(n+1);
	for(reg int i=0;i<=n;++i){
		if(i>=1)
			g0[i]=g[i-1]*(i-1)*(i-1);
		if(i>=2)
			g1[i]=g[i-2]*(i-1)*(i-1);
		if(i>=3)
			g2[i]=g[i-3]*(i-1)*(i-1);
	}
	solve(1,n);
	modInt ans=(g0[n]+g2[n])*n;
	for(reg int i=2;i<=n-2;++i)
		ans+=(g0[i]*f0[n-i]+g1[i]*f1[n-i]*2+g2[i]*f2[n-i])*i;
	printf("%d\n",ans.x);
	return 0;
}