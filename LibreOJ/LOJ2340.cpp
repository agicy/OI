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

const int MAXN=21;
const int MAXM=MAXN*(MAXN-1)/2;
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

inline void FWT_or(reg vector<int>& a,reg int flag){
	reg int n=a.size();
	for(reg int i=1;i<n;i<<=1)
		for(reg int j=0;j<n;j+=(i<<1))
			for(reg int k=0;k<i;++k)
				if(flag==1)
					a[i+j+k]=add(a[i+j+k],a[j+k]);
				else
					a[i+j+k]=sub(a[i+j+k],a[j+k]);
	return;
}

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=0;i<n;++i)
			fa[i]=i;
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
		fa[ra]=rb;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m,q;
int u[MAXM],v[MAXM];
int w[MAXN];
int deg[MAXN];
int sum[1<<MAXN],cnt[1<<MAXN],inv[1<<MAXN];
vector<int> f[MAXN+1],g[MAXN+1];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=0;i<m;++i)
		u[i]=read()-1,v[i]=read()-1;
	for(reg int i=0;i<n;++i)
		w[i]=read();
	for(reg int i=0;i<=n;++i)
		g[i].resize(1<<n);
	for(reg int S=0;S<(1<<n);++S){
		for(reg int i=0;i<n;++i)
			if((S>>i)&1)
				sum[S]+=w[i];
		fill(deg,deg+n,0);
		UnionFind::Init(n);
		reg int tmp;
		cnt[S]=tmp=__builtin_popcount(S);
		for(reg int i=0;i<m;++i)
			if((S>>u[i])&(S>>v[i])&1){
				if(!UnionFind::search(u[i],v[i]))
					--tmp,UnionFind::merge(u[i],v[i]);
				++deg[u[i]],++deg[v[i]];
			}
		reg bool flag=(tmp!=1);
		for(reg int i=0;i<n&&!flag;++i)
			if(deg[i]&1)
				flag=true;
		if(flag)
			g[cnt[S]][S]=fpow(sum[S],q);
		inv[S]=fpow(fpow(sum[S],mod-2),q);
	}
	for(reg int i=0;i<=n;++i)
		FWT_or(g[i],1);
	for(reg int i=0;i<=n;++i)
		f[i].resize(1<<n);
	f[0][0]=1;
	FWT_or(f[0],1);
	for(reg int i=1;i<=n;++i){
		for(reg int j=0;j<i;++j)
			for(reg int k=0;k<(1<<n);++k)
				f[i][k]=add(f[i][k],1ll*f[j][k]*g[i-j][k]%mod);
		FWT_or(f[i],-1);
		for(reg int j=0;j<(1<<n);++j)
			f[i][j]=(cnt[j]==i)?1ll*f[i][j]*inv[j]%mod:0;
		if(i!=n)
			FWT_or(f[i],1);
	}
	printf("%d\n",f[n].back());
	return 0;
}