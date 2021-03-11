#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

uint s;

inline uint get(reg uint x){
	x^=x<<13;
	x^=x>>17;
	x^=x<<5;
	return s=x;
}

const int MAXN=5e5+5;
const int MAXLOG2N=19+1;

int n,q;
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int Maxdep[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	Maxdep[u]=dep[u];
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs1(v,u);
		if(Maxdep[v]>Maxdep[u]){
			Maxdep[u]=Maxdep[v];
			son[u]=v;
		}
	}
	return;
}

int top[MAXN];
vector<int> up[MAXN],dn[MAXN];

inline void dfs2(reg int u,reg int topf){
	top[u]=topf;
	if(u==topf){
		up[u].resize(Maxdep[u]-dep[u]+1),dn[u].resize(Maxdep[u]-dep[u]+1);
		for(reg int i=0,v=u;i<=Maxdep[u]-dep[u];++i)
			up[u][i]=v,v=fa[v][0];
		for(reg int i=0,v=u;i<=Maxdep[u]-dep[u];++i)
			dn[u][i]=v,v=son[v];
	}
	if(!son[u])
		return;
	dfs2(son[u],topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=son[u])
			dfs2(v,v);
	}
	return;
}

int g[MAXN];

inline int getFa(reg int u,reg int k){
	if(!k)
		return u;
	else{
		u=fa[u][g[k]];
		k-=(1<<g[k])+(dep[u]-dep[top[u]]);
		u=top[u];
		return k>=0?up[u][k]:dn[u][-k];
	}
}

int main(void){
	n=read(),q=read(),s=read();
	g[0]=-1;
	for(reg int i=1;i<=n;++i)
		g[i]=g[i>>1]+1;
	for(reg int i=1;i<=n;++i)
		Add_Edge(read(),i);
	reg int rt=to[head[0]];
	dfs1(rt,0),dfs2(rt,rt);
	reg int ans=0;
	reg ll Ans=0;
	for(reg int i=1;i<=q;++i){
		reg int u=(get(s)^ans)%n+1,k=(get(s)^ans)%dep[u];
		Ans^=1ll*i*(ans=getFa(u,k));
	}
	printf("%lld\n",Ans);
	return 0;
}