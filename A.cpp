#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=512+5;

int n,m,k,s,t;
int c[MAXN];
int u[MAXM],v[MAXM];

namespace Subtask1{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
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
	inline bool check(reg int S){
		memset(vis,false,sizeof(vis));
		memset(dis,0x3f,sizeof(dis));
		dis[s]=(S>>(s-1))&1,Q.push(Node(s,dis[s]));
		while(!Q.empty()){
			static Node s;
			s=Q.top();
			Q.pop();
			reg int u=s.id;
			if(vis[u])
				continue;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+((S>>(v-1))&1)){
					dis[v]=dis[u]+((S>>(v-1))&1);
					Q.push(Node(v,dis[v]));
				}
			}
		}
		return dis[t]>=k;
	}
	inline void Solve(void){
		const int inf=2e9+5;
		reg int Min=inf,ansS=0;
		for(reg int i=1;i<=m;++i)
			Add_Edge(u[i],v[i]);
		for(reg int S=(1<<n)-1;S>=0;--S){
			if(check(S)){
				reg int sum=0;
				for(reg int i=1;i<=n;++i)
					if((S>>(i-1))&1)
						sum+=c[i];
				if(Min>sum){
					Min=sum;
					ansS=S;
				}
			}
		}
		if(Min==inf)
			puts("-1");
		else{
			vector<int> ans;
			for(int i=1;i<=n;++i)
				if((ansS>>(i-1))&1)
					ans.push_back(i);
			printf("%ld\n",ans.size());
			for(reg int i=0,siz=ans.size();i<siz;++i)
				printf("%d%c",ans[i],i==siz-1?'\n':' ');
		}
		return;
	}
}

namespace Subtask2{
	const int MAXV=2*MAXN;
	const int MAXE=(MAXN+MAXM)*2;
	const ll inf=0x3f3f3f3f3f3f3f3f;
	int cnt=1,head[MAXV],to[MAXE],Next[MAXE];
	ll w[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg ll len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg ll len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,0);
		return;
	}
	int dep[MAXV];
	int Q[MAXV];
	inline bool bfs(reg int s,reg int t){
		memset(dep,-1,sizeof(dep));
		reg int _head=0,_tail=0;
		dep[s]=1,Q[_tail++]=s;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q[_tail++]=v;
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
	bool vis[MAXV];
	inline void dfs(reg int u){
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(w[i]&&!vis[v])
				dfs(v);
		}
		return;
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			Add_Tube(i,i+n,c[i]);
		for(reg int i=1;i<=m;++i)
			Add_Tube(u[i]+n,v[i],inf);
		reg ll res=dinic(s,t+n);
		if(res>=inf)
			puts("-1");
		else{
			dfs(s);
			vector<int> ans;
			for(int i=1;i<=n;++i)
				if(vis[i]&&!vis[i+n])
					ans.push_back(i);
			printf("%ld\n",ans.size());
			for(reg int i=0,siz=ans.size();i<siz;++i)
				printf("%d%c",ans[i],i==siz-1?'\n':' ');
		}
		return;
	}
}

namespace Subtask3{
	const int MAXV=2*MAXN;
	const int MAXE=(MAXN+MAXM)*2;
	const ll inf=0x3f3f3f3f3f3f3f3f;
	int cnt=1,head[MAXV],to[MAXE],Next[MAXE];
	ll w[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg ll len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg ll len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,0);
		return;
	}
	int dep[MAXV];
	int Q[MAXV];
	inline bool bfs(reg int s,reg int t){
		memset(dep,-1,sizeof(dep));
		reg int _head=0,_tail=0;
		dep[s]=1,Q[_tail++]=s;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q[_tail++]=v;
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
	bool vis[MAXV];
	inline void dfs(reg int u){
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(w[i]&&!vis[v])
				dfs(v);
		}
		return;
	}
	bool del[MAXN];
	inline void Solve(void){
		vector<int> ans;
		reg ll res=0;
		while(k--){
			cnt=1,memset(head,0,sizeof(head));
			for(reg int i=1;i<=n;++i)
				if(!del[i])
					Add_Tube(i,i+n,c[i]);
				else
					Add_Tube(i,i+n,inf);
			for(reg int i=1;i<=m;++i)
				Add_Tube(u[i]+n,v[i],inf);
			reg ll tmp=dinic(s,t+n);
			if(tmp>=inf||res>=inf){
				puts("-1");
				return;
			}
			else{
				res+=tmp;
				memset(vis,false,sizeof(vis));
				dfs(s);
				for(int i=1;i<=n;++i)
					if(vis[i]&&!vis[i+n]){
						del[i]=true;
						ans.push_back(i);
					}
			}
		}
		printf("%ld\n",ans.size());
		for(reg int i=0,siz=ans.size();i<siz;++i)
			printf("%d%c",ans[i],i==siz-1?'\n':' ');
		return;
	}
}

int main(void){
	n=read(),m=read(),k=read(),s=read(),t=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=m;++i)
		u[i]=read(),v[i]=read();
	if(n<=12)
		Subtask1::Solve();
	else if(k==1)
		Subtask2::Solve();
	else
		puts("-1");
	return 0;
}