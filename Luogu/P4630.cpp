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

const int MAXN=100000+5,MAXM=200000+5;

int n,m,tot;
int deg[MAXN<<1];
ll ans;

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
	int fa[MAXN<<1];
	int size1[MAXN<<1],size2[MAXN<<1];
	inline void DFS1(reg int u){
		size1[u]=(u<=n);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=fa[u]){
				fa[v]=u;
				DFS1(v);
				size1[u]+=size1[v];
			}
		}
		return;
	}
	inline void DFS2(reg int u){
		if(fa[u])
			size2[u]=size2[fa[u]]+size1[fa[u]]-size1[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=fa[u])
				DFS2(v);
		}
		reg int sum=size2[u]+size1[u];
		if(u<=n){
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(v!=fa[u])
					ans+=1ll*(sum-size1[v]-1)*size1[v];
			}
			ans+=1ll*(sum-size2[u]-1)*size2[u];
		}
		else{
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(v!=fa[u])
					ans+=1ll*(sum-size1[v])*size1[v]*(deg[u]-2);
			}
			ans+=1ll*(sum-size2[u])*size2[u]*(deg[u]-2);
		}
		return;
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
					++tot;
					Tree::Add_Tube(tot,u);
					Tree::Add_Tube(tot,v);
					++deg[u],++deg[v],deg[tot]+=2;
					while(S[top]!=v){
						Tree::Add_Tube(S[top],tot);
						++deg[tot],++deg[S[top]];
						--top;
					}
					--top;
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
		Graph::Add_Tube(u,v);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::Tarjan(i);
	for(reg int i=1;i<=tot;++i)
		if(!Tree::size1[i])
			Tree::DFS1(i);
	for(reg int i=1;i<=tot;++i)
		if(!Tree::size2[i])
			Tree::DFS2(i);
	printf("%lld\n",ans);
	return 0;
}