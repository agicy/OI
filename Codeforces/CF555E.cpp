#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void No(void){
	puts("No");
	exit(0);
	return;
}

inline void Yes(void){
	puts("Yes");
	exit(0);
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXQ=2e5+5;

namespace Graph{
	const int MAXV=MAXN;
	const int MAXE=2*MAXM;
	int cnt=1,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int tim,dfn[MAXV],low[MAXV];
	bool bri[MAXE];
	inline void tarjan(reg int u,reg int id){
		dfn[u]=low[u]=++tim;
		for(reg int i=head[u];i;i=Next[i]){
			if(i==id)
				continue;
			reg int v=to[i];
			if(!dfn[v]){
				tarjan(v,i^1);
				cMin(low[u],low[v]);
				if(dfn[u]<low[v])
					bri[i]=bri[i^1]=true;
			}
			else
				cMin(low[u],dfn[v]);
		}
		return;
	}
	int col[MAXV];
	inline void dfs(reg int u,reg int c){
		col[u]=c;
		for(reg int i=head[u];i;i=Next[i])
			if(!bri[i]){
				reg int v=to[i];
				if(!col[v])
					dfs(v,c);
			}
		return;
	}
}

namespace UnionFind{
	const int MAXV=MAXN;
	int fa[MAXV];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
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
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

namespace Tree{
	const int MAXV=MAXN;
	const int MAXE=2*MAXM;
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXV],dep[MAXV];
	int siz[MAXV],son[MAXV];
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
			}
		}
		return;
	}
	int top[MAXV];
	inline void dfs2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				dfs2(v,u,v);
		}
		return;
	}
	inline int lca(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]])
				swap(u,v);
			v=fa[top[v]];
		}
		return dep[u]<dep[v]?u:v;
	}
	bool vis[MAXV];
	int up[MAXV],dn[MAXV];
	inline void dfs3(reg int u,reg int father){
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dfs3(v,u);
				up[u]+=up[v],dn[u]+=dn[v];
			}
		}
		return;
	}
}

int n,m,q;
int u[MAXM],v[MAXM];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		Graph::Add_Edge(u[i],v[i]);
		Graph::Add_Edge(v[i],u[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i,-1);
	reg int eDcc_cnt=0;
	for(reg int i=1;i<=n;++i)
		if(!Graph::col[i])
			Graph::dfs(i,++eDcc_cnt);
	UnionFind::Init(eDcc_cnt);
	for(reg int i=1;i<=m;++i)
		if(Graph::col[u[i]]!=Graph::col[v[i]]){
			UnionFind::merge(Graph::col[u[i]],Graph::col[v[i]]);
			Tree::Add_Edge(Graph::col[u[i]],Graph::col[v[i]]);
			Tree::Add_Edge(Graph::col[v[i]],Graph::col[u[i]]);
		}
	for(reg int i=1;i<=eDcc_cnt;++i)
		if(!Tree::dep[i])
			Tree::dfs1(i,0),Tree::dfs2(i,0,i);
	while(q--){
		static int s,t;
		s=read(),t=read();
		s=Graph::col[s],t=Graph::col[t];
		if(!UnionFind::search(s,t))
			No();
		if(s==t)
			continue;
		reg int lca=Tree::lca(s,t);
		++Tree::up[s],++Tree::dn[t],--Tree::up[lca],--Tree::dn[lca];
	}
	for(reg int i=1;i<=eDcc_cnt;++i)
		if(!Tree::vis[i])
			Tree::dfs3(i,0);
	for(reg int i=1;i<=eDcc_cnt;++i)
		if(Tree::up[i]&&Tree::dn[i])
			No();
	Yes();
	return 0;
}