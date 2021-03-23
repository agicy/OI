#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=2003;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

namespace Poly{
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	struct Complex{
		double x,y;
		inline Complex(reg double x=0,reg double y=0):x(x),y(y){
			return;
		}
		inline Complex operator+(const Complex& a)const{
			return Complex(x+a.x,y+a.y);
		}
		inline Complex operator-(const Complex& a)const{
			return Complex(x-a.x,y-a.y);
		}
		inline Complex operator*(const Complex& a)const{
			return Complex(x*a.x-y*a.y,y*a.x+x*a.y);
		}
	};
	const double pi=acos(-1.0);
	inline void FFT(reg vector<Complex>& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			Complex w(cos(pi/i),flag*sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=e*a[i+j+k];
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1)
			for(reg int i=0;i<limit;++i)
				a[i].x/=limit;
		return;
	}
	typedef vector<int> poly;
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		vector<Complex> ta,tb;
		ta.resize(limit),tb.resize(limit);
		for(reg int i=0,siz=a.size();i<siz;++i)
			ta[i]=Complex(a[i],0);
		for(reg int i=0,siz=b.size();i<siz;++i)
			tb[i]=Complex(b[i],0);
		FFT(ta,limit,1),FFT(tb,limit,1);
		for(reg int i=0;i<limit;++i)
			ta[i]=ta[i]*tb[i];
		FFT(ta,limit,-1);
		a.resize(s);
		for(reg int i=0;i<s;++i)
			a[i]=((int)(ta[i].x+0.5))%mod;
		return a;
	}
	inline poly getStrling2(reg int n){
		poly a,b;
		a.resize(n+1),b.resize(n+1);
		for(reg int i=0,fac=1;i<=n;++i,fac=1ll*fac*i%mod){
			reg int invfac=fpow(fac,mod-2);
			a[i]=((i&1)?(mod-1ll):1ll)*invfac%mod;
			b[i]=1ll*fpow(i,n)*invfac%mod;
		}
		poly res=mul(a,b);
		res.resize(n+1);
		return res;
	}
}

using namespace Poly;

int n,K,L,F;

int main(void){
	scanf("%d%d%d%d",&n,&K,&L,&F);
	poly f=getStrling2(F);
	poly res=f,x=f;
	reg int exp=L-1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		res.resize(min((int)res.size(),mod)),x.resize(min((int)x.size(),mod));
		exp>>=1;
	}
	reg int invk=fpow(K%mod,mod-2);
	reg int ans=0;
	for(reg int i=0,bas=1;i<=min(L*F,mod-1);++i,bas=1ll*bas*((n-i+1)%mod)%mod*invk%mod)
		ans=add(ans,1ll*bas*res[i]%mod);
	printf("%d\n",ans);
	return 0;
}