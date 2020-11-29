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

const int MAXN=1e3+5;
const int MAXM=1e4+5;
const int MAXK=100+5;
const int MAXE=1e7+5;

int n,m,k;

namespace pGraph{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id,dis;
		inline Node(reg int id=0,reg int dis=0):id(id),dis(dis){
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
	int dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void Dijkstra(reg int s){
		memset(vis,false,sizeof(vis));
		memset(dis,0x3f,sizeof(dis));
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
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id,f,h;
		inline Node(reg int id=0,reg int f=0,reg int h=0):id(id),f(f),h(h){
			return;
		}
		inline bool operator<(const Node& a)const{
			return f>a.f;
		}
	};
	int vis[MAXN];
	priority_queue<Node> Q;
	int tot,ans[MAXK];
	inline void Astar(reg int s,reg int t,reg int k){
		memset(vis,0,sizeof(vis));
		memset(ans,-1,sizeof(ans));
		Q.push(Node(s,0,0));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			++vis[u];
			if(u==t){
				ans[++tot]=s.f;
				if(tot==k)
					return;
			}
			if(vis[u]>k)
				continue;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				reg int h=s.h+w[i];
				reg int f=h+pGraph::dis[v];
				Q.push(Node(v,f,h));
			}
		}
		return;
	}
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,d;
		x=read(),y=read(),d=read();
		Graph::Add_Edge(x,y,d);
		pGraph::Add_Edge(y,x,d);
	}
	pGraph::Dijkstra(1);
	Graph::Astar(n,1,k);
	for(reg int i=1;i<=k;++i)
		printf("%d\n",Graph::ans[i]);
	return 0;
}