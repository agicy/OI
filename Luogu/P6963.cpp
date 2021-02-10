#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)){if(ch==EOF)exit(0);ch=getchar();}
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXLOG2N=20;

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int i=head[u];i;i=Next[i]){
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

int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
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

struct querys{
	int u,v,lca,len;
	inline bool operator<(const querys& q)const{
		return len<q.len;
	}
};

querys q[MAXN];

namespace UnionFind{
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int q,reg int b){
		reg int ra=find(q),rb=find(b);
		if(ra!=rb){
			fa[rb]=ra;
			siz[ra]+=siz[rb];
		}
		return;
	}
}

int n,f;

int main(void){
	n=read(),f=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	for(reg int i=1;i<=f;++i){
		q[i].u=read(),q[i].v=read(),q[i].lca=LCA(q[i].u,q[i].v);
		q[i].len=dep[q[i].u]+dep[q[i].v]-(dep[q[i].lca]<<1);
	}
	sort(q+1,q+f+1);
	UnionFind::Init(n);
	for(reg int i=1;i<=f;++i){
		reg int p,d=dep[q[i].lca];
		p=UnionFind::find(q[i].u);
		while(dep[p]>d)
			UnionFind::merge(fa[p],p),p=UnionFind::find(p);
		p=UnionFind::find(q[i].v);
		while(dep[p]>d)
			UnionFind::merge(fa[p],p),p=UnionFind::find(p);
		if(q[i].len!=UnionFind::siz[UnionFind::find(q[i].lca)]-1){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}