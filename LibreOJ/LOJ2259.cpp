#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int cnt=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))cnt=10*cnt+(ch^'0'),ch=getchar();
	return cnt;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=3e4+5;
const int MAXM=6e4+5;
const int inf=0x3f3f3f3f;

int n,m,k;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
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
int from[MAXN];
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
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				from[v]=u;
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
			else if(dis[v]==dis[u]+w[i]&&u<from[v])
				from[v]=u;
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
	int top;
	Node S[MAXN];
	Node a[MAXN];
	inline void dfs(reg int u,reg int father){
		S[++top]=a[u];
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
				top=0;
				dfs(v,u);
				for(reg int j=1;j<=top;++j){
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
				for(reg int j=1;j<=top;++j)
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
		del[u]=true;
		calc(u);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!del[v]){
				rt=0,MaxPart=inf,sum=siz[v];
				getRt(v,0),solve(rt);
			}
		}
		return;
	}
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c),Add_Edge(b,a,c);
	}
	dijkstra(1);
	for(reg int i=1;i<=n;++i)
		if(from[i]){
			Tree_Conquer::Add_Edge(i,from[i],dis[i]-dis[from[i]]);
			Tree_Conquer::Add_Edge(from[i],i,dis[i]-dis[from[i]]);
		}
	using namespace Tree_Conquer;
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	printf("%d %d\n",ans1,ans2);
	return 0;
}