#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;
const int MAXLOG2N=19+1;

int n,m;
int cnt,head[MAXM],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int ecc_cnt,col[MAXN];

inline void tarjan(reg int u,reg int fa){
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(v!=fa)
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++ecc_cnt;
		do{
			v=S[top--];
			col[v]=ecc_cnt;
		}while(v!=u);
	}
	return;
}

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

vector<Edge> G[MAXN];
int fa[MAXN][MAXLOG2N],dep[MAXN];
int tag[MAXN];
int dis[MAXN];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dis[u]+=tag[u];
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=0;i<(int)G[u].size();++i)
		if(G[u][i].v!=father){
			dis[G[u][i].v]=dis[u]+G[u][i].w;
			dfs(G[u][i].v,u);
		}
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		Add_Edge(x,y,z),Add_Edge(y,x,z);
	}
	tarjan(1,0);
	for(reg int i=1;i<=n;++i)
		for(reg int j=head[i];j;j=Next[j])
			if(col[i]==col[to[j]])
				tag[col[i]]+=w[j];
			else
				G[col[i]].push_back(Edge(col[to[j]],w[j]));
	dfs(1,0);
	reg int q=read();
	while(q--){
		static int u,v,lca;
		u=col[read()],v=col[read()],lca=LCA(u,v);
		puts(dis[u]+dis[v]-(dis[lca]<<1)+tag[lca]>0?"YES":"NO");
	}
	return 0;
}