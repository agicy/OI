#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
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

int n,q;
int fac[MAXN],invfac[MAXN];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

namespace UnionFind{
	int fa[MAXN],siz[MAXN],val[MAXN];
	inline void Init(reg int n){
		for(reg int i=0;i<n;++i)
			fa[i]=i,siz[i]=val[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		siz[ra]+=siz[rb];
		val[ra]=1ll*val[ra]*val[rb]%mod*binom(siz[ra]-1,siz[rb])%mod;
		fa[rb]=ra;
		return;
	}
}

int main(void){
	n=read(),q=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	UnionFind::Init(n);
	reg int lastans=0;
	while(q--){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=(read()+lastans)%n,y=(read()+lastans)%n;
				UnionFind::merge(y,x);
				break;
			}
			case 2:{
				x=(read()+lastans)%n;
				writeln(lastans=UnionFind::val[UnionFind::find(x)]);
				break;
			}
		}
	}
	flush();
	return 0;
}