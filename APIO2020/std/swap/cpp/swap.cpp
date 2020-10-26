#include"swap.h"

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

const int MAX=4e5+5;
const int MAXLOG2N=19+1;
const int inf=0x3f3f3f3f;

Edge E[MAX];

int n,m;
int cnt,head[MAX],to[MAX],Next[MAX];
int tot;
int fa[MAX],in[MAX],Max[MAX],res[MAX],val[MAX];
bool tag[MAX];
int f[MAX][MAXLOG2N],dep[MAX];
int deg[MAX];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(reg int a,reg int b,reg int w){
	if(a==b)
		return;
	++in[a],++in[b];
	reg int ra=find(a),rb=find(b);
	++tot;
	Add_Edge(tot,ra);
	++deg[ra];
	if(ra!=rb)
		Add_Edge(tot,rb),++deg[rb];
	fa[ra]=fa[rb]=tot;
	Max[tot]=max(max(Max[ra],Max[rb]),max(in[a],in[b]));
	val[tot]=w;
	if(ra==rb||Max[tot]>2)
		tag[tot]=true;
	return;
}

inline void dfs(reg int u){
	for(reg int i=1;i<MAXLOG2N;++i)
		f[u][i]=f[f[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(tag[v])
			res[v]=val[v];
		else
			res[v]=res[u];
		f[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
	return;
}

inline int lca(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[f[y][i]]>=dep[x])
			y=f[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

void init(int N,int M,vector<int> U,vector<int> V,vector<int> W){
	n=tot=N,m=M;
	for(reg int i=1;i<=m;++i)
		E[i]=Edge(U[i-1]+1,V[i-1]+1,W[i-1]);
	sort(E+1,E+m+1);
	for(reg int i=1;i<MAX;++i)
		fa[i]=i,in[i]=0;
	for(reg int i=1;i<=m;++i){
		reg int x=find(E[i].u),y=find(E[i].v);
		if(x==y&&tag[x])
			continue;
		merge(E[i].u,E[i].v,E[i].w);
	}
	for(reg int i=1;i<=tot;++i){
		if(deg[i])
			continue;
		if(tag[i])
			res[i]=val[i];
		else
			res[i]=inf;
		dep[i]=1;
		dfs(i);
	}
	return;
}

int getMinimumFuelCapacity(int x,int y){
	reg int l=lca(x+1,y+1);
	return res[l]==inf?-1:res[l];
}