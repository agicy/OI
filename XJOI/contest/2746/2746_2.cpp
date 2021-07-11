#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int lg(reg int x){
	return __builtin_ffs(x)-1;
}

const int MAXK=18;
const int mod=998244353;

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
	typedef vector<int> poly;
	inline void FWT_or(reg poly& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					a[i+j+k]=add(a[i+j+k],a[j+k]);
		return;
	}
	inline void iFWT_or(reg poly& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					a[i+j+k]=sub(a[i+j+k],a[j+k]);
		return;
	}
	inline poly ln(const poly& a){
		reg int siz=a.size(),lim=lg(a.size());
		static vector<poly> f,g;
		f.resize(lim+1),g.resize(lim+1);
		for(reg int i=0;i<=lim;++i){
			f[i].resize(siz),fill(f[i].begin(),f[i].end(),0);
			g[i].resize(siz),fill(g[i].begin(),g[i].end(),0);
		}
		for(reg int i=0;i<siz;++i)
			f[__builtin_popcount(i)][i]=a[i];
		for(reg int i=0;i<=lim;++i)
			FWT_or(f[i]);
		for(reg int i=0;i<=lim;++i)
			if(!i)
				fill(g[i].begin(),g[i].end(),1);
			else{
				for(reg int j=0;j<i;++j)
					for(reg int S=0;S<siz;++S)
						g[i][S]=add(g[i][S],1ll*j*g[j][S]%mod*f[i-j][S]%mod);
				reg int inv=fpow(i,mod-2);
				for(reg int S=0;S<siz;++S)
					g[i][S]=sub(f[i][S],1ll*inv*g[i][S]%mod);
			}
		for(reg int i=0;i<=lim;++i)
			iFWT_or(g[i]);
		poly res(siz);
		for(reg int i=0;i<siz;++i)
			res[i]=g[__builtin_popcount(i)][i];
		return res;
	}
	inline poly exp(const poly& a){
		reg int siz=a.size(),lim=lg(a.size());
		static vector<poly> f,g;
		f.resize(lim+1),g.resize(lim+1);
		for(reg int i=0;i<=lim;++i){
			f[i].resize(siz),fill(f[i].begin(),f[i].end(),0);
			g[i].resize(siz),fill(g[i].begin(),g[i].end(),0);
		}
		for(reg int i=0;i<siz;++i)
			f[__builtin_popcount(i)][i]=a[i];
		for(reg int i=0;i<=lim;++i)
			FWT_or(f[i]);
		for(reg int i=0;i<=lim;++i)
			if(!i)
				fill(g[i].begin(),g[i].end(),1);
			else{
				for(reg int j=1;j<=i;++j)
					for(reg int S=0;S<siz;++S)
						g[i][S]=add(g[i][S],1ll*j*f[j][S]%mod*g[i-j][S]%mod);
				reg int inv=fpow(i,mod-2);
				for(reg int S=0;S<siz;++S)
					g[i][S]=1ll*inv*g[i][S]%mod;
			}
		for(reg int i=0;i<=lim;++i)
			iFWT_or(g[i]);
		poly res(siz);
		for(reg int i=0;i<siz;++i)
			res[i]=g[__builtin_popcount(i)][i];
		return res;
	}
}

ll a,b;
int k;
int p[MAXK],c[MAXK];
int Phi[1<<MAXK];

inline int getF(reg int S){
	reg int x=1;
	for(reg int T=S;T;T^=lowbit(T))
		x=1ll*x*p[lg(lowbit(T))]%mod;
	return add(sub(1ll*x*x%mod,x),1);
}

Poly::poly f;

bool ed;

int main(void){
	a=readll()%mod,b=readll()%mod,k=read();
	for(reg int i=0;i<k;++i)
		p[i]=read(),c[i]=read();
	f.resize(1<<k);
	for(reg int i=0;i<(1<<k);++i)
		f[i]=getF(i);
	f=Poly::ln(f);
	for(reg int i=0;i<(1<<k);++i)
		f[i]=b*f[i]%mod;
	f=Poly::exp(f);
	reg int ans=0;
	for(reg int S=0;S<(1<<k);++S){
		if(!S)
			Phi[S]=1;
		else
			Phi[S]=1ll*Phi[S^lowbit(S)]*(p[lg(lowbit(S))]-1)%mod;
		if(__builtin_parity(S))
			ans=sub(ans,1ll*Phi[S]*fpow(a,__builtin_popcount(S))%mod*f[S]%mod);
		else
			ans=add(ans,1ll*Phi[S]*fpow(a,__builtin_popcount(S))%mod*f[S]%mod);
	}
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}