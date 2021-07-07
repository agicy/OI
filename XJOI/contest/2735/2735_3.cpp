#include "hypercube.h"
#include<bits/stdc++.h>
using namespace std;

const int MAXN=3e3+5;

int n;
bool vis[MAXN];
vector<int> G[MAXN];
int fa[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(int u){
	siz[u]=1;
	son[u]=0;
	for(int v:G[u]){
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
			son[u]=v;
	}
	return;
}

int top[MAXN],leaf[MAXN];

inline void dfs2(int u,int topf){
	top[u]=topf;
	if(!son[u]){
		leaf[u]=u;
		return;
	}
	dfs2(son[u],topf),leaf[u]=leaf[son[u]];
	for(int v:G[u])
		if(v!=son[u]&&v!=fa[u])
			dfs2(v,v);
	return;
}

inline void rebuild(void){
	for(int i=1;i<=n;++i)
		if(vis[i])
			G[i].clear();
	for(int i=1;i<=n;++i)
		if(fa[i])
			G[fa[i]].push_back(i);
	dfs1(1),dfs2(1,1);
	return;
}

int dep[MAXN];

inline int query(int x,int y){
	return query(x,vector<int>{y});
}

inline bool check(int x,int pre,int y){
	static vector<int> tmp;
	tmp.clear();
	int res=0;
	for(int i=0;i<pre;++i)
		tmp.push_back(G[x][i]),res^=dep[G[x][i]];
	res^=query(y,tmp);
	if(pre&1)
		res^=dep[y];
	return !((!res&&!(pre&1))||(res==x&&(pre&1)));
}

inline int LCA(int x,int y){
	return dep[x]^dep[y]^query(x,y);
}

inline void insert(int topf,int x){
	int lf=leaf[topf],lca=LCA(lf,x);
	if(lca==lf){
		fa[x]=lf;
		return;
	}
	if(vis[lca]){
		int tmp=query(x,G[lca]);
		for(int v:G[lca])
			tmp^=dep[v];
		bool odd=G[lca].size()&1;
		if(odd)
			tmp^=dep[x];
		if((!tmp&&!odd)||(tmp==lca&&odd)){
			fa[x]=lca;
			return;
		}
		if(!odd)
			tmp^=lca;
		if(tmp!=x&&vis[tmp]){
			insert(tmp,x);
			return;
		}
		int __l=1,__r=G[lca].size(),__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(check(lca,__mid,x))
				__r=__mid;
			else
				__l=__mid+1;
		}
		vis[tmp]=true;
		fa[tmp]=lca,fa[G[lca][__l-1]]=tmp;
		if(tmp!=x)
			fa[x]=tmp;
		return;
	}
	if(x!=lca)
		fa[x]=lca,vis[lca]=true;
	int tot=0;
	static int V[MAXN];
	for(int i=lf;top[i]==topf;i=fa[i])
		V[++tot]=i;
	int __l=1,__r=tot,__mid;
	while(__l<__r){
		__mid=(__l+__r)>>1;
		if(LCA(V[__mid],lca)==lca)
			__l=__mid+1;
		else
			__r=__mid;
	}
	fa[V[__l-1]]=lca;
	fa[lca]=V[__l];
	return;
}

void solve(int n,int Q,int data_type){
	for(int i=1;i<=n;++i)
		vis[i]=false,dep[i]=query(1,i),fa[i]=0,G[i].clear();
	::n=n;
	vis[1]=true;
	for(int i=2;i<=n;++i)
		if(!vis[i]){
			rebuild();
			insert(1,i);
			vis[i]=true;
		}
	for(int i=2;i<=n;++i)
		report(i,fa[i]);
	return;
}