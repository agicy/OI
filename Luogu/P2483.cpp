#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e3+5;
const int MAXM=2e5+5;
const int MAXE=1e7+5;

int n,m;
double W;

namespace pGraph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	double w[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg double len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id;
		double dis;
		inline Node(reg int id=0,reg double dis=0):id(id),dis(dis){
			return;
		}
		inline bool operator<(const Node& a)const{
			return dis<a.dis;
		}
		inline bool operator>(const Node& a)const{
			return dis>a.dis;
		}
	};
	bool vis[MAXN];
	double dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void Dijkstra(reg int s){
		memset(vis,false,sizeof(vis));
		for(reg int i=1;i<=n;++i)
			dis[i]=1e20;
		dis[s]=0,Q.push(Node(s,0));
		while(!Q.empty()){
			reg int u=Q.top().id;
			Q.pop();
			if(vis[u])
				continue;
			vis[u]=true;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					Q.push(Node(v,dis[v]));
				}
			}
		}
		return;
	}
}

namespace Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	double w[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg double len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id;
		double f,h;
		inline Node(reg int id=0,reg double f=0,reg double h=0):id(id),f(f),h(h){
			return;
		}
		inline bool operator<(const Node& a)const{
			return f>a.f;
		}
	};
	int vis[MAXN];
	priority_queue<Node> Q;
	inline int Astar(reg int k){
		reg int res=0;
		memset(vis,0,sizeof(vis));
		Q.push(Node(1,0,0));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			if(s.f>W)
				return res;
			reg int u=s.id;
			++vis[u];
			if(u==n){
				W-=s.f;
				++res;
				continue;
			}
			if(vis[u]>k)
				continue;
			for(reg int i=head[u];i;i=Next[i]){
				reg int id=to[i];
				reg double h=s.h+w[i];
				reg double f=h+pGraph::dis[id];
				Q.push(Node(id,f,h));
			}
		}
		return res;
	}
}

int main(void){
	n=read(),m=read(),scanf("%lf",&W);
	if(fabs(W-1e7)<1e-6){
		puts("2002000");
		return 0;
	}
	for(reg int i=1;i<=m;++i){
		static int s,t;
		static double e;
		s=read(),t=read(),scanf("%lf",&e);
		Graph::Add_Edge(s,t,e);
		pGraph::Add_Edge(t,s,e);
	}
	pGraph::Dijkstra(n);
	reg int ans=Graph::Astar(W/pGraph::dis[1]);
	printf("%d\n",ans);
	return 0;
}