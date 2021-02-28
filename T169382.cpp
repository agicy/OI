#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXLOG22N=19+1;
const int inf=0x3f3f3f3f;

int n;
int rt,MaxPart;

namespace DivTree{
	int tot;
	bool del[MAXN];
	int siz[MAXN];
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
		ll dis[MAXN];
		ll st[MAXLOG22N][MAXN<<1];
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
		inline ll getDis(int u,int v){
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
		inline void getRt(reg int u,reg int father){
			siz[u]=1;
			int Max=0;
			for(auto x:G[u]){
				reg int v=x.v;
				if(v!=father&&!del[v]){
					getRt(v,u);
					siz[u]+=siz[v];
					Max=max(Max,siz[v]);
				}
			}
			Max=max(Max,tot-siz[u]);
			if(Max<MaxPart)
				rt=u,MaxPart=Max;
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
				tot=siz[v];
				MaxPart=inf,rt=0;
				Tree::getRt(v,0);
				Add_Edge(u,rt,v);
				build(rt,u);
			}
		}
		return;
	}
	inline void update(reg int u){
		++sumv[u];
		for(reg int i=u;fa[i];i=fa[i]){
			reg ll dis=Tree::getDis(fa[i],u);
			dis1[fa[i]]+=dis;
			dis2[i]+=dis;
			++sumv[fa[i]];
		}
		return;
	}
	inline ll calc(reg int u){
		reg ll res=dis1[u];
		for(reg int i=u;fa[i];i=fa[i]){
			reg ll dis=Tree::getDis(fa[i],u);
			res+=dis1[fa[i]]-dis2[i]+dis*(sumv[fa[i]]-sumv[i]);
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
	n=read();
	for(reg int i=2;i<=n;++i){
		static int p,c;
		p=read(),c=read();
		DivTree::Tree::Add_Edge(i,p,c);
		DivTree::Tree::Add_Edge(p,i,c);
	}
	DivTree::Tree::InitRMQ();
	DivTree::tot=n;
	MaxPart=inf,rt=0;
	DivTree::Tree::getRt(1,0);
	reg int Root=rt;
	DivTree::build(rt,0);
	for(reg int i=1;i<=n;++i){
		DivTree::update(i);
		writeln(DivTree::query(Root));
	}
	flush();
	return 0;
}