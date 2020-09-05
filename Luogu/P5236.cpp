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

const int MAXN=10000+5;
const int MAXM=20000+5;

int n,m,q;
int tot;

namespace Tree{
	int cnt,head[MAXN<<1],to[MAXN<<2],w[MAXN<<2],Next[MAXN<<2];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXN<<1],dep[MAXN<<1];
	int size[MAXN<<1],son[MAXN<<1];
	int dis[MAXN<<1];
	inline void DFS1(reg int u,reg int father){
		size[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i])
			if(to[i]!=father){
				dis[to[i]]=dis[u]+w[i];
				DFS1(to[i],u);
				size[u]+=size[to[i]];
				if(size[son[u]]<size[to[i]])
					son[u]=to[i];
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
	inline int find(reg int lca,reg int x){
		reg int res=0;
		while(top[x]!=top[lca]){
			res=top[x];
			x=fa[top[x]];
		}
		return x==lca?res:son[lca];
	}
}

int sum[MAXN<<1];

namespace Graph{
	int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],b[MAXN];
	int tim,dfn[MAXN],low[MAXN];
	inline void Solve(int u,int v,int w){
		++tot;
		reg int pre=w,i=v;
		while(i!=fa[u]){
			sum[i]=pre;
			pre+=b[i];
			i=fa[i];
		}
		sum[tot]=sum[u];
		sum[u]=0;
		i=v;
		while(i!=fa[u]){
			reg int pw=min(sum[i],sum[tot]-sum[i]);
			Tree::Add_Edge(tot,i,pw);
			Tree::Add_Edge(i,tot,pw);
			i=fa[i];
		}
	}
	inline void Tarjan(reg int u,reg int father){
		dfn[u]=low[u]=++tim;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v==father)
				continue;
			if(!dfn[v]){
				fa[v]=u,b[v]=w[i];
				Tarjan(v,u);
				low[u]=min(low[u],low[v]);
			}
			else
				low[u]=min(low[u],dfn[v]);
			if(low[v]<=dfn[u])
				continue;
			Tree::Add_Edge(u,v,w[i]);
			Tree::Add_Edge(v,u,w[i]);
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(fa[v]==u||dfn[v]<=dfn[u])
				continue;
			Solve(u,v,w[i]);
		}
		return;
	}
}

int main(void){
	n=read(),m=read(),q=read();
	tot=n;
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Graph::Add_Edge(u,v,w);
		Graph::Add_Edge(v,u,w);
	}
	Graph::Tarjan(1,0);
	Tree::DFS1(1,0);
	Tree::DFS2(1,0,1);
	while(q--){
		static int u,v;
		u=read(),v=read();
		reg int lca=Tree::LCA(u,v);
		reg int ans;
		if(lca<=n)
			ans=Tree::dis[u]+Tree::dis[v]-2*Tree::dis[lca];
		else{
			int a=Tree::find(lca,u),b=Tree::find(lca,v);
			ans=Tree::dis[u]+Tree::dis[v]-Tree::dis[a]-Tree::dis[b];
			if(sum[a]<sum[b])
				swap(a,b);
			ans+=min(sum[a]-sum[b],sum[lca]+sum[b]-sum[a]);
		}
		printf("%d\n",ans);
	}
	return 0;
}