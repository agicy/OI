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

const int MAXN=1e5+5;
const int mod=998244353;

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

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int deg[MAXN];
int siz[MAXN],fa[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			deg[u]+=deg[v];
			siz[u]+=siz[v];
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		++deg[u],++deg[v];
		Add_Edge(u,v),Add_Edge(v,u);
	}
	reg int sum=0;
	for(reg int i=1;i<=n;++i)
		sum+=deg[i];
	dfs(1,0);
	reg int ans=0;
	for(reg int u=1;u<=n;++u)
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v==fa[u])
				ans=add(ans,1ll*deg[u]*siz[u]%mod*(n-siz[u])%mod);
			else
				ans=add(ans,1ll*(sum-deg[v])*(n-siz[v])%mod*siz[v]%mod);
		}
	printf("%lld\n",1ll*ans*fpow(1ll*n*n%mod,mod-2)%mod);
	return 0;
}