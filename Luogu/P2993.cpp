#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int cnt=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))cnt=10*cnt+(ch^'0'),ch=getchar();
	return cnt;
}

const int MAXN=3e4+5;
const int MAXM=6e4+5;
const int inf=0x3f3f3f3f;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return v<a.v;
	}
};

vector<Edge> G[MAXN];

int n,m,k;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

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
		for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
			reg int v=it->v,w=it->w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

namespace Tree_Conquer{
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int rt,MaxPart,sum;
	bool del[MAXN];
	int siz[MAXN];
	inline void getRt(reg int u,reg int father){
		siz[u]=1;
		reg int Max=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&!del[v]){
				getRt(v,u);
				siz[u]+=siz[v];
				Max=max(Max,siz[v]);
			}
		}
		Max=max(Max,sum-Max);
		if(Max<MaxPart)
			rt=u,MaxPart=Max;
		return;
	}
	struct Node{
		int dep,dis;
		inline Node(reg int dep=0,reg int dis=0):dep(dep),dis(dis){
			return;
		}
		inline Node operator+(const Node& a)const{
			return Node(dep+a.dep,dis+a.dis);
		}
	};
	Node S[MAXN];
	int tot;
	Node a[MAXN];
	inline void dfs(reg int u,reg int father){
		S[++tot]=a[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&!del[v]){
				a[v]=a[u]+Node(1,w[i]);
				dfs(v,u);
			}
		}
		return;
	}
	int ans1,ans2;
	int T[MAXN],Max[MAXN];
	inline void calc(reg int u){
		reg int MaxDep=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!del[v]){
				a[v]=Node(1,w[i]);
				tot=0;
				dfs(v,u);
				for(reg int j=1;j<=tot;++j){
					reg int w=S[j].dis;
					if(S[j].dep<k-1){
						reg int cnt=k-S[j].dep-1;
						if(w+Max[cnt]>ans1)
							ans1=w+Max[cnt],ans2=T[cnt];
						else if(w+Max[cnt]==ans1)
							ans2+=T[cnt];
					}
					else if(S[j].dep==k-1){
						if(w>ans1)
							ans1=w,ans2=1;
						else if(w==ans1)
							++ans2;
					}
				}
				for(reg int j=1;j<=tot;++j)
					if(S[j].dep<=k-1){
						reg int dep=S[j].dep;
						if(S[j].dis>Max[dep])
							T[dep]=1,Max[dep]=S[j].dis;
						else if(S[j].dis==Max[dep])
							++T[dep];
						MaxDep=max(MaxDep,dep);
					}
			}
		}
		for(reg int i=1;i<=MaxDep;++i)
			T[i]=0,Max[i]=0;
		return;
	}
	inline void solve(reg int u){
		calc(u);
		del[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!del[v]){
				rt=0,MaxPart=inf,sum=siz[v];
				getRt(v,u),solve(rt);
			}
		}
		return;
	}
}

inline void build(reg int u){
	vis[u]=true;
	for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=it->v,w=it->w;
		if(!vis[v]&&dis[u]+w==dis[v]){
			Tree_Conquer::Add_Edge(u,v,w);
			Tree_Conquer::Add_Edge(v,u,w);
			build(v);
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		G[u].push_back(Edge(v,w));
		G[v].push_back(Edge(u,w));
	}
	for(reg int i=1;i<=n;++i)
		sort(G[i].begin(),G[i].end());
	dijkstra(1);
	memset(vis,false,sizeof(vis));
	build(1);
	using namespace Tree_Conquer;
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	printf("%d %d\n",ans1,ans2);
	return 0;
}