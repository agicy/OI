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

const int MAXN=500+5;
const int MAXM=5e3+5;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=MAXN*2;
	const int MAXE=(MAXN*4+MAXM)*2;
	int cnt,head[MAXV],to[MAXE],w[MAXE],p[MAXE],nxt[MAXE];
	inline void init(reg int s,reg int t){
		cnt=1,fill(head+s,head+t+1,0);
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int lim,reg int cot){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=lim,p[cnt]=cot;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int lim,reg int cot){
		Add_Edge(u,v,lim,cot);
		Add_Edge(v,u,0,-cot);
		return;
	}
	bool inque[MAXV];
	ll dis[MAXV];
	int cur[MAXV];
	inline bool spfa(int s,reg int t){
		const ll inf=0x3f3f3f3f3f3f3f3f;
		fill(dis+s,dis+t+1,inf);
		queue<int> Q;
		inque[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false,cur[u]=head[u];
			for(reg int i=head[u];i;i=nxt[i]){
				int v=to[i];
				if(dis[v]>dis[u]+p[i]&&w[i]){
					dis[v]=dis[u]+p[i];
					if(!inque[v]){
						inque[v]=true;
						Q.push(v);
					}
				}
			}
		}
		return dis[t]!=inf;
	}
	bool vis[MAXV];
	inline int dfs(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		vis[u]=true;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=nxt[i]){
			reg int v=to[i];
			if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f,w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		vis[u]=false;
		return flow;
	}
	inline pair<int,ll> dinic(reg int s,reg int t){
		int flow=0;
		ll cost=0;
		while(spfa(s,t)){
			reg int f=dfs(s,t,inf);
			flow+=f,cost+=f*dis[t];
		}
		return make_pair(flow,cost);
	}
}

int n,m;

int main(void){
	n=read(),m=read();
	reg int s=0,t=2*n+1;
	Network::init(s,t);
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		Network::Add_Tube(s,i,1,0);
		Network::Add_Tube(i+n,t,1,0);
		Network::Add_Tube(i,i+n,1,x);
		Network::Add_Tube(i+n,i,inf,0);
	}
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		Network::Add_Tube(x,y+n,inf,z);
	}
	printf("%lld\n",Network::dinic(s,t).second);
	return 0;
}