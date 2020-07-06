#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;
const int MAXQ=100000+5;


int n,m,q;
int tot;
int dis[MAXN<<1];

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
	inline void DFS1(reg int u,reg int father){
		size[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		reg int tmp=-1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				DFS1(v,u);
				size[u]+=size[v];
				if(tmp<size[v]){
					son[u]=v;
					tmp=size[v];
				}
			}
		}
		return;
	}
	int top[MAXN<<1];
	int tim,dfn[MAXN<<1],rnk[MAXN<<1];
	inline void DFS2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		dfn[u]=++tim;
		rnk[dfn[u]]=u;
		if(!son[u])
			return;
		DFS2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				DFS2(v,u,v);
		}
		return;
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int Min[MAXN<<3];
	#define Min(x) Min[(x)]
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			Min(k)=dis[Tree::rnk[l]];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int tim,reg int val){
		if(l==r){
			Min(k)=val;
			return;
		}
		if(tim<=mid)
			Update(lson,l,mid,tim,val);
		else
			Update(rson,mid+1,r,tim,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Min(k);
		int res=INF;
		if(L<=mid)
			res=min(res,Query(lson,l,mid,L,R));
		if(R>mid)
			res=min(res,Query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int Query(int u,int v){
	using namespace Tree;
	int res=INF;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		res=min(res,SegmentTree::Query(1,1,tot,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	res=min(res,SegmentTree::Query(1,1,tot,dfn[u],dfn[v]));
	if(u>n)
		res=min(res,dis[fa[u]]);
	return res;
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
				if(low[v]==dfn[u]){
					++tot;
					reg int To;
					do{
						To=S[top--];
						Tree::Add_Tube(tot,To);
					}while(To!=v);
					Tree::Add_Tube(tot,u);
				}
			}
			else
				low[u]=min(low[u],dfn[v]);
		}
		return;
	}
}

multiset<int> S[MAXN<<1];

int main(void){
	n=read(),m=read(),q=read();
	tot=n;
	for(reg int i=1;i<=n;++i)
		dis[i]=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Graph::Add_Tube(u,v);
	}
	Graph::Tarjan(1);
	Tree::DFS1(1,0);
	Tree::DFS2(1,0,1);
	using namespace Tree;
	for(reg int i=1;i<=n;++i)
		if(fa[i])
			S[fa[i]].insert(dis[i]);
	for(reg int i=n+1;i<=tot;++i)
		dis[i]=*S[i].begin();
	SegmentTree::Build(1,1,tot);
	while(q--){
		static char opt;
		static int a,b,w;
		do
			opt=getchar();
		while(opt!='A'&&opt!='C');
		switch(opt){
			case 'A':{
				a=read(),b=read();
				printf("%d\n",Query(a,b));
				break;
			}
			case 'C':{
				a=read(),w=read();
				SegmentTree::Update(1,1,tot,dfn[a],w);
				if(fa[a]){
					S[fa[a]].erase(S[fa[a]].lower_bound(dis[a]));
					S[fa[a]].insert(w);
					if(dis[fa[a]]!=*S[fa[a]].begin()){
						dis[fa[a]]=*S[fa[a]].begin();
						SegmentTree::Update(1,1,tot,dfn[fa[a]],dis[fa[a]]);
					}
				}
				dis[a]=w;
				break;
			}
			default:break;
		}
	}
	return 0;
}