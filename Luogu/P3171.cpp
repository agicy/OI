#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=500+5;
const int MAXM=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m;
int u[MAXM],v[MAXM],w[MAXM];
int c[MAXN];

namespace dijkstra{
	struct Edge{
		int v,w;
		inline Edge(reg int v=0,reg int w=0):v(v),w(w){
			return;
		}
	};
	vector<Edge> G[MAXN];
	inline void build(void){
		for(reg int i=1;i<=m;++i)
			G[u[i]].push_back(Edge(v[i],w[i])),G[v[i]].push_back(Edge(u[i],w[i]));
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
	bool vis[MAXN];
	ll dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void dijkstra(reg int s){
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0,Q.push(Node(s,dis[s]));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			if(vis[u])
				continue;
			vis[u]=true;
			for(Edge e:G[u]){
				reg int v=e.v,w=e.w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					Q.push(Node(v,dis[v]));
				}
			}
		}
		return;
	}
}

namespace Network{
	const int MAXV=2*MAXN;
	const int MAXE=(MAXN+MAXM)*2;
	int cnt=1,head[MAXV],to[MAXE],Next[MAXE];
	ll w[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg ll len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg ll len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,0ll);
		return;
	}
	int dep[MAXV];
	queue<int> Q;
	inline bool bfs(int s,reg int t){
		memset(dep,-1,sizeof(dep));
		dep[s]=1,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q.push(v);
				}
			}
		}
		return dep[t]!=-1;
	}
	int cur[MAXV];
	inline ll dfs(reg int u,reg int t,reg ll lim){
		if(u==t)
			return lim;
		reg ll flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]){
				reg ll f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f;
					w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		return flow;
	}
	inline ll dinic(reg int s,reg int t){
		reg ll res=0;
		while(bfs(s,t)){
			memcpy(cur,head,sizeof(head));
			res+=dfs(s,t,inf);
		}
		return res;
	}
	inline void build(void){
		reg ll *dis=dijkstra::dis;
		for(reg int i=1;i<=n;++i)
			Add_Tube(i,i+n,c[i]);
		for(reg int i=1;i<=m;++i){
			if(dis[u[i]]==dis[v[i]]+::w[i])
				Add_Tube(v[i]+n,u[i],inf);
			if(dis[v[i]]==dis[u[i]]+::w[i])
				Add_Tube(u[i]+n,v[i],inf);
		}
		return;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		u[i]=read(),v[i]=read(),w[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	dijkstra::build();
	dijkstra::dijkstra(1);
	Network::build();
	reg int s=1+n,t=n;
	printf("%lld\n",Network::dinic(s,t));
	return 0;
}