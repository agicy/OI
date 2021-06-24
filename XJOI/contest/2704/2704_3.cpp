#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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
	inline modInt operator-(void){
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

const int MAXN=1e6+5;

modInt fac[MAXN],invfac[MAXN],inv[MAXN];

inline int lg(reg int x){
	switch(x){
		case 0:return -1;
		case 1<<0 ... (1<<1)-1:return 0;
		case 1<<1 ... (1<<2)-1:return 1;
		case 1<<2 ... (1<<3)-1:return 2;
		case 1<<3 ... (1<<4)-1:return 3;
		case 1<<4 ... (1<<5)-1:return 4;
		case 1<<5 ... (1<<6)-1:return 5;
		case 1<<6 ... (1<<7)-1:return 6;
		case 1<<7 ... (1<<8)-1:return 7;
		case 1<<8 ... (1<<9)-1:return 8;
		case 1<<9 ... (1<<10)-1:return 9;
		case 1<<10 ... (1<<11)-1:return 10;
		case 1<<11 ... (1<<12)-1:return 11;
		case 1<<12 ... (1<<13)-1:return 12;
		case 1<<13 ... (1<<14)-1:return 13;
		case 1<<14 ... (1<<15)-1:return 14;
		case 1<<15 ... (1<<16)-1:return 15;
		case 1<<16 ... (1<<17)-1:return 16;
		case 1<<17 ... (1<<18)-1:return 17;
		case 1<<18 ... (1<<19)-1:return 18;
		case 1<<19 ... (1<<20)-1:return 19;
		case 1<<20 ... (1<<21)-1:return 20;
		case 1<<21 ... (1<<22)-1:return 21;
		default:assert(false);return -1;
	}
}

namespace Poly{
	const modInt g=3;
	const modInt invg=332748118;
	vector<vector<modInt>> w;
	inline void init(reg int k){
		w.resize(k+1);
		for(reg int i=1;i<=k;++i){
			w[i].resize(1<<i);
			modInt wn=fpow(g,(mod-1)>>i);
			w[i][0]=1;
			for(reg int j=1;j<(1<<i);++j)
				w[i][j]=w[i][j-1]*wn;
		}
		return;
	}
	typedef vector<modInt> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		vector<int> rev(limit);
		reg int l=lg(limit);
		for(reg int i=0;i<limit;++i){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		}
		for(reg int i=1,lg=0;i<limit;i<<=1,++lg)
			for(reg int j=0;j<limit;j+=(i<<1))
				for(reg int k=0;k<i;++k){
					modInt x=a[j+k],y=w[lg+1][k]*a[i+j+k];
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
		if(flag==-1){
			reverse(a.begin()+1,a.end());
			modInt inv=fpow(limit,mod-2);
			for(reg int i=0;i<limit;++i)
				a[i]*=inv;
		}
		return;
	}
	inline poly der(poly a){
		for(reg int i=0,siz=a.size();i<siz-1;++i)
			a[i]=a[i+1]*(i+1);
		a.pop_back();
		return a;
	}
	inline poly itg(poly a){
		a.resize(a.size()+1);
		for(reg int i=a.size()-1;i>0;--i)
			a[i]=a[i-1]*::inv[i];
		a[0]=0;
		return a;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=1<<(lg(s-1)+1);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]*=b[i];
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
	inline poly inv(poly a){
		reg int deg=a.size();
		if(deg==1)
			return poly{fpow(a[0],mod-2)};
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Inv=inv(tmp);
		reg int limit=1<<(lg((deg<<1)-1)+1);
		Inv.resize(limit,0),a.resize(limit,0);
		NTT(Inv,limit,1),NTT(a,limit,1);
		for(reg int i=0;i<limit;++i)
			Inv[i]=(-a[i]*Inv[i]+2)*Inv[i];
		NTT(Inv,limit,-1);
		Inv.resize(deg);
		return Inv;
	}
	inline poly ln(const poly& a){
		poly res=itg(mul(der(a),inv(a)));
		res.resize(a.size());
		return res;
	}
}

//using namespace Poly;

int n;

bool ed;

int main(void){
	scanf("%d",&n);
	Poly::init(lg(n-1)+2);
	fac[0]=1;
	for(reg int i=1;i<=n+1;++i)
		fac[i]=fac[i-1]*i;
	invfac[n+1]=fpow(fac[n+1],mod-2);
	for(reg int i=n;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	for(reg int i=1;i<=n+1;++i)
		inv[i]=invfac[i]*fac[i-1];
	Poly::poly a;
	a.resize(n+1);
	static modInt bas2[MAXN];
	bas2[0]=1;
	for(reg int i=1;i<=n;++i)
		bas2[i]=bas2[i-1]+bas2[i-1];
	a[0]=1;
	for(reg int i=1;i<=n;++i)
		a[i]=a[i-1]*bas2[i-1];
	for(reg int i=0;i<=n;++i)
		a[i]*=invfac[i];
	a=Poly::ln(a);
	modInt ans=(a[n]*fac[n]+((n&1)?-fac[n-1]:fac[n-1]))*fpow(2,mod-2);
	printf("%d\n",ans.x);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}