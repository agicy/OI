#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXM=1e6+5;

namespace Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	bool vis[MAXN];
	int tim,dfn[MAXN],low[MAXN];
	int top,S[MAXN];
	int scc_cnt,col[MAXN];
	inline void tarjan(reg int u){
		vis[u]=true;
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!dfn[v]){
				tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(vis[v])
				low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u]){
			++scc_cnt;
			reg int v;
			do{
				v=S[top--];
				vis[v]=false;
				col[v]=scc_cnt;
			}while(v!=u);
		}
		return;
	}
}

namespace Dijkstra{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int id,val;
		inline Node(reg int id=0,reg int val=0):id(id),val(val){
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
	int dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline int dijkstra(reg int s,reg int t){
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0,Q.push(Node(s,dis[s]));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			if(vis[u])
				continue;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					Q.push(Node(v,dis[v]));
				}
			}
		}
		return dis[t];
	}
}

int n,m;
int u[MAXM],v[MAXM],w[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read(),w[i]=read();
		Graph::Add_Edge(u[i],v[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int i=1;i<=m;++i)
		if(Graph::col[u[i]]!=Graph::col[v[i]])
			Dijkstra::Add_Edge(Graph::col[u[i]],Graph::col[v[i]],w[i]);
	reg int res=Dijkstra::dijkstra(Graph::col[1],Graph::col[n]);
	printf("%d\n",res);
	return 0;
}