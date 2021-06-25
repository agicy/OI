#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXM=200000+5;
const int MAXQ=100000+5;
const int MAXS=200000+5;

int n,m;
int tot;

namespace Tree{
	int cnt,head[MAXN<<1],to[MAXN<<2],Next[MAXN<<2];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v);
		Add_Edge(v,u);
		return;
	}
	int fa[MAXN<<1],dep[MAXN<<1];
	int son[MAXN<<1],size[MAXN<<1];
	int dis[MAXN<<1];
	inline void DFS1(reg int u,reg int father){
		size[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dis[v]=dis[u]+(v<=n);
				DFS1(v,u);
				size[u]+=size[v];
				if(size[son[u]]<size[v])
					son[u]=v;
			}
		}
		return;
	}
	int tim,dfn[MAXN<<1];
	int top[MAXN<<1];
	inline void DFS2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		dfn[u]=++tim;
		if(son[u])
			DFS2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				DFS2(v,u,v);
		}
		return;
	}
	inline int LCA(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])
				swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}
}

namespace Graph{
	int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v);
		Add_Edge(v,u);
		return;
	}
	int tim,dfn[MAXN],low[MAXN];
	int top,S[MAXN];
	inline void Tarjan(reg int u){
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!dfn[v]){
				Tarjan(v);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u]){
					Tree::Add_Tube(++tot,u);
					reg int x;
					do{
						x=S[top--];
						Tree::Add_Tube(tot,x);
					}while(x!=v);
				}
			}
			else
				low[u]=min(low[u],dfn[v]);
		}
		return;
	}
}

inline void Init(void){
	Tree::cnt=Tree::tim=Graph::cnt=Graph::tim=0;
	for(reg int i=1;i<=n;++i)
		Graph::head[i]=0;
	for(reg int i=1;i<=tot;++i)
		Tree::head[i]=Tree::dfn[i]=0;
	tot=n;
	return;
}

inline int GetAns(reg int x,reg int y){
	reg int lca=Tree::LCA(x,y);
	return Tree::dis[x]+Tree::dis[y]-(Tree::dis[lca]<<1);
}

int p[MAXS];

inline bool cmp(reg int a,reg int b){
	return Tree::dfn[a]<Tree::dfn[b];
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read();
		Init();
		for(reg int i=1;i<=m;++i){
			static int u,v;
			u=read(),v=read();
			Graph::Add_Tube(u,v);
		}
		Graph::Tarjan(1);
		Tree::dis[1]=1;
		Tree::DFS1(1,0);
		Tree::DFS2(1,0,1);
		reg int q=read();
		while(q--){
			reg int s=read();
			for(reg int i=1;i<=s;++i)
				p[i]=read();
			sort(p+1,p+s+1,cmp);
			p[s+1]=p[1];
			reg int ans=0,x=0;
			for(reg int i=1;i<=s;++i)
				x+=GetAns(p[i],p[i+1]);
			ans=x/2-s+(Tree::LCA(p[1],p[s])<=n);
			printf("%d\n",ans);
		}
	}
	return 0;
}