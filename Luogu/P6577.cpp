#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=500+5;
const int MAXM=MAXN*MAXN/2+5;
const int MAXV=MAXN*2;
const int MAXE=(2*MAXN+MAXM)*2;
const int inf=0x3f3f3f3f;

int n,m;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

int dis[MAXV];
bool inque[MAXV];
queue<int> Q;

inline bool spfa(int s,reg int t){
	memset(dis,0x3f,sizeof(dis));
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
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

ll cost;
bool vis[MAXV];
int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		cost+=1ll*dis[t]*lim;
		return lim;
	}
	vis[u]=true;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
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
	cost=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int y,c,h;
		y=read(),c=read(),h=read();
		Add_Tube(y,c+n,1,-h);
	}
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,1,0),Add_Tube(i+n,t,1,0);
	dinic(s,t);
	printf("%lld\n",-cost);
	for(reg int u=1;u<=n;++u)
		for(reg int j=head[u+n];j;j=Next[j]){
			reg int v=to[j];
			if(v!=t&&w[j]){
				printf("%d%c",v,u==n?'\n':' ');
				break;
			}
		}
	return 0;
}