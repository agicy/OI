#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXLOG22N=18+1;
const int inf=0x3f3f3f3f;

int n,Q;
int root,MaxPart;

namespace DivTree{
	int tot;
	bitset<MAXN> del;
	int size[MAXN];
	namespace Tree{
		struct Edge{
			int v,w;
			inline Edge(reg int v=0,reg int w=0):v(v),w(w){
				return;
			} 
		};
		vector<Edge> G[MAXN];
		inline void Add_Edge(reg int u,reg int v,reg int len){
			G[u].push_back(Edge(v,len));
			return;
		}
		int dis[MAXN];
		int st[MAXLOG22N][MAXN<<1];
		int tim,pos[MAXN];
		inline void dfs(reg int u,reg int father){
			pos[u]=++tim;
			st[0][tim]=dis[u];
			for(auto x:G[u]){
				reg int v=x.v,w=x.w;
				if(v!=father){
					dis[v]=dis[u]+w;
					dfs(v,u);
					st[0][++tim]=dis[u];
				}
			}
			return;
		}
		int Log[MAXN<<1];
		inline int getDis(int u,int v){
			if(pos[u]>pos[v])
				swap(u,v);
			reg int k=Log[pos[v]-pos[u]+1];
			return dis[u]+dis[v]-2*min(st[k][pos[u]],st[k][pos[v]-(1<<k)+1]);
		}
		inline void InitRMQ(void){
			dfs(1,0);
			Log[0]=-1;
			for(reg int i=1;i<=tim;++i)
				Log[i]=Log[i>>1]+1;
			for(reg int i=1;(1<<i)<=tim;++i)
				for(reg int j=1;j+(1<<i)-1<=tim;++j)
					st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
			return;
		}
		inline void getRoot(reg int u,reg int father){
			size[u]=1;
			int Max=0;
			for(auto x:G[u]){
				reg int v=x.v;
				if(v!=father&&!del[v]){
					getRoot(v,u);
					size[u]+=size[v];
					Max=max(Max,size[v]);
				}
			}
			Max=max(Max,tot-size[u]);
			if(Max<MaxPart){
				root=u;
				MaxPart=Max;
			}
			return;
		}
	}
	struct Edge{
		int v,w;
		inline Edge(reg int v=0,reg int w=0):v(v),w(w){
			return;
		}
	};
	vector<Edge> G[MAXN];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		G[u].push_back(Edge(v,len));
		return;
	}
	int fa[MAXN];
	ll dis1[MAXN],dis2[MAXN],sumv[MAXN];
	inline void build(reg int u,reg int father){
		del[u]=true;
		fa[u]=father;
		for(auto x:Tree::G[u]){
			reg int v=x.v;
			if(!del[v]){
				tot=size[v];
				MaxPart=inf,root=0;
				Tree::getRoot(v,0);
				Add_Edge(u,root,v);
				build(root,u);
			}
		}
		return;
	}
	inline void update(reg int u,reg int e){
		sumv[u]+=e;
		for(reg int i=u;fa[i];i=fa[i]){
			reg int dis=Tree::getDis(fa[i],u);
			dis1[fa[i]]+=1ll*dis*e;
			dis2[i]+=1ll*dis*e;
			sumv[fa[i]]+=e;
		}
		return;
	}
	inline ll calc(reg int u){
		reg ll res=dis1[u];
		for(reg int i=u;fa[i];i=fa[i]){
			reg int dis=Tree::getDis(fa[i],u);
			res+=dis1[fa[i]]-dis2[i]+1ll*dis*(sumv[fa[i]]-sumv[i]);
		}
		return res;
	}
	inline ll query(reg int u){
		reg ll res=calc(u);
		for(auto x:G[u]){
			reg int v=x.v,w=x.w;
			reg ll tmp=calc(w);
			if(tmp<res)
				return query(v);
		}
		return res;
	}
}

int main(void){
	n=read(),Q=read();
	for(reg int i=1;i<n;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		DivTree::Tree::Add_Edge(a,b,c);
		DivTree::Tree::Add_Edge(b,a,c);
	}
	DivTree::Tree::InitRMQ();
	DivTree::tot=n;
	MaxPart=inf,root=0;
	DivTree::Tree::getRoot(1,0);
	reg int Root=root;
	DivTree::build(root,0);
	while(Q--){
		static int u,e;
		u=read(),e=read();
		DivTree::update(u,e);
		printf("%lld\n",DivTree::query(Root));
	}
	return 0;
}