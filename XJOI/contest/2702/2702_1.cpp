#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

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
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]*=b[i];
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
}

const int MAXN=152501+5;

int n,k;
int p[MAXN];
bool vis[MAXN];
modInt fac[MAXN],invfac[MAXN];

inline void init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	return;
}

inline modInt binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m];
}

Poly::poly f[MAXN];

inline Poly::poly solve(reg int l,reg int r){
	if(l==r)
		return f[l];
	else{
		reg int mid=(l+r)>>1;
		return Poly::mul(solve(l,mid),solve(mid+1,r));
	}
}

int main(void){
	init(152501);
	reg int t=read();
	while(t--){
		n=read(),k=read();
		for(reg int i=1;i<=n;++i)
			p[i]=read();
		fill(vis+1,vis+n+1,false);
		reg int tot=0;
		static int siz[MAXN];
		for(reg int i=1;i<=n;++i){
			if(!vis[i]){
				reg int ptr=i;
				reg int cnt=0;
				while(!vis[ptr]){
					vis[ptr]=true;
					ptr=p[ptr];
					++cnt;
				}
				siz[++tot]=cnt;
			}
		}
		if(k<tot)
			puts("0");
		else{
			random_shuffle(siz+1,siz+tot+1);
			for(reg int i=1;i<=tot;++i){
				f[i].resize(siz[i]);
				for(reg int j=1;j<=siz[i];++j)
					f[i][j-1]=binom(siz[i],j);
			}
			Poly::poly tmp=solve(1,tot);
			modInt ans1=tmp[k-tot];
			modInt ans2=binom(n,k);
			modInt ans=ans1*fpow(ans2,mod-2);
			printf("%d\n",ans.x);
		}
	}
	return 0;
}