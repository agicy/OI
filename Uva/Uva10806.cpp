#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXM=MAXN*(MAXN-1)/2;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=MAXN;
	const int MAXE=(MAXM*2)*2;
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
	int dis[MAXV];
	int cur[MAXV];
	inline bool spfa(int s,reg int t){
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
	inline pair<int,int> dinic(reg int s,reg int t){
		int flow=0,cost=0;
		while(spfa(s,t)){
			reg int f=dfs(s,t,inf);
			flow+=f,cost+=f*dis[t];
		}
		return make_pair(flow,cost);
	}
}

int n,m;

int main(void){
	while(scanf("%d",&n)!=EOF&&n!=0){
		scanf("%d",&m);
		reg int s=0,t=n+1;
		Network::init(s,t);
		Network::Add_Tube(s,1,2,0);
		Network::Add_Tube(n,t,2,0);
		for(reg int i=1;i<=m;++i){
			static int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			Network::Add_Tube(u,v,1,w);
			Network::Add_Tube(v,u,1,w);
		}
		pair<int,int> ans=Network::dinic(s,t);
		if(ans.first<2)
			puts("Back to jail");
		else
			printf("%d\n",ans.second);
	}
	return 0;
}