#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;
const int MAXM=1e5+5;

int n,m,q;

namespace Tree{
	const int MAXV=2*MAXN;
	const int MAXLOG2V=15+1;
	const int MAXE=MAXV*2;
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	bool vis[MAXV];
	int fa[MAXV][MAXLOG2V],dep[MAXV];
	inline void dfs(reg int u){
		vis[u]=true;
		for(reg int i=1;i<MAXLOG2V;++i){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			if(!fa[u][i])
				break;
		}
		for(reg int i=head[u];i!=-1;i=Next[i]){
			reg int v=to[i];
			if(vis[v])
				continue;
			fa[v][0]=u;
			dep[v]=dep[u]+1;
			dfs(v);
		}
		return;
	}
	inline int LCA(int x,int y){
		if(dep[x]<dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(dep[fa[x][i]]>=dep[y])
				x=fa[x][i];
		if(x==y)
			return x;
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline void Init(void){
		memset(vis,false,sizeof(vis));
		cnt=0,memset(head,-1,sizeof(head));
		memset(fa,0,sizeof(fa)),memset(dep,0,sizeof(dep));
		return;
	}
}

stack<int> E;
int col[MAXM];

namespace Graph{
	const int MAXV=MAXN;
	const int MAXE=2*MAXM;
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int tim,dfn[MAXV],low[MAXV];
	int top,S[MAXV];
	int fa[MAXV];
	int V;
	inline void tarjan(reg int u){
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u];i!=-1;i=Next[i]){
			reg int v=to[i];
			if(!dfn[v]){
				fa[v]=u;
				E.push((i+1)/2);
				tarjan(v);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u]){
					reg int tmp;
					++V;
					do{
						tmp=S[top--];
						Tree::Add_Edge(V,tmp);
						Tree::Add_Edge(tmp,V);
					}while(tmp!=v);
					Tree::Add_Edge(V,u);
					Tree::Add_Edge(u,V);
					while(true){
						reg int id=E.top();
						E.pop();
						col[id]=V;
						if(id==(i+1)/2)
							break;
					}
				}
			}
			else if(v!=fa[u]){
				low[u]=min(low[u],dfn[v]);
				if(dfn[v]<dfn[u])
					E.push((i+1)/2);
			}
		}
		return;
	}
	inline void Init(void){
		cnt=0,memset(head,-1,sizeof(head));
		tim=0,memset(dfn,0,sizeof(dfn));
		memset(fa,0,sizeof(fa));
		top=0;
		return;
	}
}

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF&&(n!=0||m!=0)){
		Tree::Init();
		Graph::Init();
		Graph::V=n;
		while(!E.empty())E.pop();
		memset(col,0,sizeof(col));
		for(reg int i=1;i<=m;++i){
			static int x,y;
			scanf("%d%d",&x,&y);
			Graph::Add_Edge(x,y);
			Graph::Add_Edge(y,x);
		}
		for(reg int i=1;i<=n;++i)
			if(!Graph::dfn[i]){
				Graph::tarjan(i);
				Tree::dep[i]=1;
				Tree::dfs(i);
			}
		scanf("%d",&q);
		while(q--){
			static int u,v;
			using Tree::dep;
			using Tree::LCA;
			scanf("%d%d",&u,&v);
			reg int x=col[u],y=col[v];
			reg int lca=LCA(x,y);
			printf("%d\n",(dep[x]+dep[y]-2*dep[lca])/2);
		}
	}
	return 0;
}