#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e6+5;
const int mod=99991;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,q;
int a[MAXN];
int u[MAXN],v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN];
int sum1[MAXN];

inline void dfs1(reg int u,reg int father){
	sum1[u]=a[u];
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			sum1[u]=add(sum1[u],sum1[v]);
		}
	}
	return;
}

int f[MAXN];
int pf[MAXN];

inline void dfs2(reg int u,reg int father){
	f[u]=sum1[u];
	pf[u]=1ll*sum1[u]*sum1[u]%mod;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs2(v,u);
			f[u]=add(f[u],f[v]);
			pf[u]=add(pf[u],pf[v]);
		}
	}
	return;
}

int sum2[MAXN];
int g[MAXN];
int pg[MAXN];

inline void dfs3(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){

			g[v]=g[u];
			g[v]=add(g[v],f[u]);
			g[v]=sub(g[v],f[v]);
			g[v]=add(g[v],sum2[v]);
			g[v]=sub(g[v],sum1[u]);

			pg[v]=pg[u];
			pg[v]=add(pg[v],pf[u]);
			pg[v]=sub(pg[v],pf[v]);
			pg[v]=add(pg[v],1ll*sum2[v]*sum2[v]%mod);
			pg[v]=sub(pg[v],1ll*sum1[u]*sum1[u]%mod);

			dfs3(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()%mod;
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read();
		Add_Edge(u[i],v[i]),Add_Edge(v[i],u[i]);
	}
	dfs1(1,0);
	for(reg int i=1;i<=n;++i)
		sum2[i]=sub(sum1[1],sum1[i]);
	dfs2(1,0),dfs3(1,0);
	reg ll sum=0;
	reg int XOR=0;
	for(reg int i=1;i<=q;++i){
		static int x;
		x=read();
		reg int son=dep[u[x]]<dep[v[x]]?v[x]:u[x];
		reg int ans1=1ll*sum2[son]*sub(1ll*sum1[son]*f[son]%mod,pf[son])%mod;
		reg int ans2=1ll*sum1[son]*sub(1ll*sum2[son]*g[son]%mod,pg[son])%mod;
		reg int ans=add(ans1,ans2);
		sum+=ans,XOR^=ans;
	}
	printf("%lld\n%d\n",sum,XOR);
	return 0;
}