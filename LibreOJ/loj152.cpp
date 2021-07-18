#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

namespace Poly{
	const int mod=1e9+9;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=mod?a-mod:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+mod:a;
	}
	typedef vector<int> poly;
	inline void FWT_or(poly& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					a[i+j+k]=add(a[i+j+k],a[j+k]);
		return;
	}
	inline void iFWT_or(poly& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					a[i+j+k]=sub(a[i+j+k],a[j+k]);
		return;
	}
	inline poly mul(const poly& a,const poly& b){
		assert(a.size()==b.size());
		reg int lim=a.size();
		reg int lg=__builtin_ctz(lim);
		vector<poly> f,g,h;
		f.resize(lg+1),g.resize(lg+1),h.resize(lg+1);
		for(reg int i=0;i<=lg;++i)
			f[i].resize(lim),g[i].resize(lim),h[i].resize(lim);
		for(reg int i=0;i<lim;++i){
			f[__builtin_popcount(i)][i]=a[i];
			g[__builtin_popcount(i)][i]=b[i];
		}
		for(reg int i=0;i<=lg;++i)
			FWT_or(f[i]),FWT_or(g[i]);
		for(reg int i=0;i<=lg;++i)
			for(reg int j=0;i+j<=lg;++j)
				for(reg int k=0;k<lim;++k)
					h[i+j][k]=add(h[i+j][k],1ll*f[i][k]*g[j][k]%mod);
		for(reg int i=0;i<=lg;++i)
			iFWT_or(h[i]);
		poly res;
		res.resize(lim);
		for(reg int i=0;i<lim;++i)
			res[i]=h[__builtin_popcount(i)][i];
		return res;
	}
}

int n;

bool ed;

int main(void){
	n=read();
	Poly::poly f(1<<n),g(1<<n);
	for(reg int i=0;i<(1<<n);++i)
		f[i]=read();
	for(reg int i=0;i<(1<<n);++i)
		g[i]=read();
	Poly::poly h=Poly::mul(f,g);
	for(reg int i=0;i<(1<<n);++i)
		write(h[i]),putchar(i==(1<<n)-1?'\n':' ');
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3f MiB\n",(&ed-&st)/1048576.0);
	return 0;
}