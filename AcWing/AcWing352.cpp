#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],siz[MAXN];

inline void dfs1(int u,int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
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

inline void dfs2(int u,int father,int topf){
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
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

int val[MAXN],sum[MAXN];
int ans;

inline void dfs3(int u,int father){
	sum[u]=val[u];
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v!=father){
			dfs3(v,u);
			sum[u]+=sum[v];
		}
	}
	if(u!=1){
		if(sum[u]==0)
			ans+=m;
		else if(sum[u]==1)
			++ans;
	}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		Add_Edge(a,b),Add_Edge(b,a);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	for(int i=1;i<=m;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		int lca=LCA(a,b);
		val[lca]-=2,++val[a],++val[b];
	}
	dfs3(1,0);
	printf("%d\n",ans);
	return 0;
}