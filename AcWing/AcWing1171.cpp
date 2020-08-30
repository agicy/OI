#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;
const int MAXM=2e4+5;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int dis[MAXN];
int son[MAXN],siz[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=dis[u]+w[i];
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
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<n;++i){
		static int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		Add_Edge(x,y,k);
		Add_Edge(y,x,k);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	while(m--){
		static int x,y;
		scanf("%d%d",&x,&y);
		reg int lca=LCA(x,y);
		reg int d=dis[x]+dis[y]-(dis[lca]<<1);
		printf("%d\n",d);
	}
	return 0;
}