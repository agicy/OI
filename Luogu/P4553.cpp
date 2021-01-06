#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXM=79+5;
const int MAXV=2*MAXN;
const int MAXE=2*(3*MAXN+MAXN*MAXN/2);
const int inf=1e10;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len,p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXV];
int dis[MAXV];
int Q[MAXV*100];

inline bool spfa(reg int s,reg int t){
	reg int h=0,ta=0;
	fill(dis,dis+MAXV,inf);
	inque[s]=true,dis[s]=0,Q[ta++]=s;
	while(h<ta){
		reg int u=Q[h++];
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]){
				dis[v]=dis[u]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q[ta++]=v;
				}
			}
		}
	}
	return dis[t]<inf;
}

int cost;
bool vis[MAXV];
int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		cost+=dis[t]*lim;
		return lim;
	}
	reg int flow=0;
	vis[u]=true;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]&&dis[v]==dis[u]+p[i]&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	vis[u]=false;
	return flow;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int n,m;

signed main(void){
	n=read(),m=read();
	reg int tmpS=2*n+2,t=2*n+1;
	reg int s=0;
	Add_Tube(s,tmpS,min(n,m),0);
	for(reg int i=1;i<=n;++i)
		Add_Tube(tmpS,i,inf,0),Add_Tube(i+n,t,inf,0);
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		static int v;
		v=read();
		Add_Tube(i,i+n,v,-inf);
		sum+=v;
	}
	for(reg int i=1;i<n;++i)
		for(reg int j=i+1;j<=n;++j){
			static int x;
			x=read();
			if(x==-1)
				continue;
			Add_Tube(i+n,j,inf,x);
		}
	dinic(s,t);
	printf("%lld\n",cost+sum*inf);
	return 0;
}