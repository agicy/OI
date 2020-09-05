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

const int MAXN=500000+5;
const int MAXM=1000000+5;
const int MAXQ=500000+5;

int n,m,q;
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
	int size[MAXN<<1],son[MAXN<<1];
	inline void DFS1(reg int u,reg int father){
		size[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				DFS1(v,u);
				size[u]+=size[v];
				if(size[son[u]]<size[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN<<1];
	inline void DFS2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(son[u])
			DFS2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i])
			if(to[i]!=father&&to[i]!=son[u])
				DFS2(to[i],u,to[i]);
		return;
	}
	inline int LCA(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])
				swap(x,y);
			x=fa[top[x]];
		}
		return dep[x]<dep[y]?x:y;
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
	int top,S[MAXN];
	int tim,dfn[MAXN],low[MAXN];
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

int main(void){
	n=read(),m=read();
	tot=n;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Graph::Add_Edge(u,v);
		Graph::Add_Edge(v,u);
	}
	Graph::Tarjan(1);
	Tree::DFS1(1,0);
	Tree::DFS2(1,0,1);
	q=read();
	while(q--){
		static int u,v;
		u=read(),v=read();
		using namespace Tree;
		reg int lca=LCA(u,v);
		reg int ans=((dep[u]+dep[v]-(dep[lca]<<1))>>1)+1;
		printf("%d\n",ans);
	}
	return 0;
}