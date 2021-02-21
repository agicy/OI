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

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
ll f[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
			f[u]+=f[v]+siz[v];
		}
	}
	return;
}

int top[MAXN];
ll g[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	if(!son[u])
		return;
	g[son[u]]=g[u]+n+f[u]-f[son[u]]-(siz[son[u]]<<1);
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u]){
			g[v]=g[u]+n+f[u]-f[v]-(siz[v]<<1);
			dfs2(v,u,v);
		}
	}
	return;
}

inline int LCA(reg int x,reg int y){
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]])
			x=fa[top[x]];
		else
			y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}

inline int getSon(reg int x,reg int rt){
	while(top[x]!=top[rt]){
		if(fa[top[x]]==rt)
			return top[x];
		x=fa[top[x]];
	}
	return son[rt];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0);
	g[1]=0;
	dfs2(1,0,1);
	while(m--){
		static int u,v;
		u=read(),v=read();
		reg int lca=LCA(u,v);
		reg double ans;
		if(lca==u||lca==v){
			if(lca==v)
				swap(u,v);
			reg int son=getSon(v,u);
			ans=(dep[v]-dep[u]+1)+1.0*(g[u]+f[u]-f[son]-siz[son])/(n-siz[son])+1.0*f[v]/siz[v];
		}
		else{
			reg int dis=dep[u]+dep[v]-(dep[lca]<<1);
			ans=(dis+1.0)+1.0*f[u]/siz[u]+1.0*f[v]/siz[v];
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}