#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}
const int mod=1e9+7;

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
		x*=x;
		exp>>=1;
	}
	return res;
}

namespace Poly{
	typedef vector<modInt> poly;
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			printf("%d%c",a[i].x,i==siz-1?'\n':' ');
		return;
	}
	inline poly mul(poly a,poly b){
		poly res;
		res.resize(a.size()+b.size()-1);
		for(reg int i=0,siza=a.size();i<siza;++i)
			for(reg int j=0,sizb=b.size();j<sizb;++j)
				res[i+j]+=a[i]*b[j];
		return res;
	}
}

using namespace Poly;

const int MAXN=300+5;
const int S=4e4;
const int MAXS=4e4+5;

bool vis[MAXS];
int tot,prime[MAXS];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

inline int getVal(reg int x){
	for(reg int i=1;i<=tot&&1ll*prime[i]*prime[i]<=x;++i)
		while(!(x%(prime[i]*prime[i])))
			x/=prime[i]*prime[i];
	return x;
}

int n;
int a[MAXN],b[MAXN];
modInt fac[MAXN],invfac[MAXN];

int main(void){
	Init(4e4);
	n=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	for(reg int i=1;i<=n;++i)
		a[i]=getVal(read());
	sort(a+1,a+n+1);
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(a[i]!=a[i-1])
			b[++tot]=1;
		else
			++b[tot];
	poly f{1};
	for(reg int i=1;i<=tot;++i){
		poly g;
		g.resize(b[i]);
		modInt pod=1;
		for(reg int j=b[i];j>=1;--j){
			g[b[i]-j]=pod*invfac[b[i]-j];
			pod=pod*j*(j-1);
		}
		f=mul(f,g);
	}
	modInt ans=0;
	for(reg int i=0,siz=f.size();i<siz;++i)
		if(i&1)
			ans-=f[i]*fac[n-i];
		else
			ans+=f[i]*fac[n-i];
	printf("%d\n",ans.x);
	return 0;
}