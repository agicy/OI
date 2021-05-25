#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=3e3+5;
const int MAXM=3e3+5;

struct Edge{
	int u,v,w;
};

int n,m,k;
Edge e[MAXM];

namespace Graph{
	struct Edge{
		int v,w;
		inline Edge(reg int v=0,reg int w=0):v(v),w(w){
			return;
		}
	};
	vector<Edge> G[MAXN];
	inline void Init(void){
		for(reg int i=1;i<=n;++i)
			G[i].clear();
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int w){
		G[u].push_back(Edge(v,w));
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int w){
		Add_Edge(u,v,w),Add_Edge(v,u,w);
		return;
	}
	struct Node{
		int id;
		ll val;
		inline Node(reg int id=0,reg ll val=0):id(id),val(val){
			return;
		}
		inline bool operator<(const Node& a)const{
			return val<a.val;
		}
		inline bool operator>(const Node& a)const{
			return val>a.val;
		}
	};
	const ll inf=0x3f3f3f3f3f3f3f3f;
	bool vis[MAXN];
	ll dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline ll dijkstra(reg int s,reg int t){
		fill(vis+1,vis+n+1,false);
		fill(dis+1,dis+n+1,inf);
		while(!Q.empty()) Q.pop();
		dis[s]=0,Q.push(Node(s,dis[s]));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			if(vis[u])
				continue;
			vis[u]=true;
			if(u==t)
				break;
			for(Edge e:G[u])
				if(dis[e.v]>dis[u]+e.w){
					dis[e.v]=dis[u]+e.w;
					Q.push(Node(e.v,dis[e.v]));
				}
		}
		return dis[t];
	}
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		e[i].u=read(),e[i].v=read(),e[i].w=read();
		Graph::Add_Tube(e[i].u,e[i].v,e[i].w);
	}
	reg ll ans=Graph::dijkstra(1,n);
	for(reg int i=1;i<=m;++i){
		Graph::Init();
		for(reg int j=1;j<=m;++j)
			if(e[j].w>e[i].w)
				Graph::Add_Tube(e[j].u,e[j].v,e[j].w-e[i].w);
			else
				Graph::Add_Tube(e[j].u,e[j].v,0);
		ans=min(ans,Graph::dijkstra(1,n)+1ll*k*e[i].w);
	}
	printf("%lld\n",ans);
	return 0;
}