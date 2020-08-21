#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200000+5;
const int MAXV=2*MAXN;
const int MAXE=2*(MAXN*3+MAXN*2);
const int inf=0x3f3f3f3f;

int n,k,l;
int a[MAXN],b[MAXN];
int cnt,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

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

bitset<MAXV> inque;
int dis[MAXV];
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
int cur[MAXV];
bitset<MAXV> vis;

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
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	vis[u]=false;
	return flow;
}

inline int dinic(reg int s,reg int t){
	cost=0;
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=1,memset(head,0,sizeof(head));
		n=read(),k=read(),l=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			b[i]=read();
		reg int s=0,t=2*n+1,ts=2*n+2,tt=2*n+3;
		for(reg int i=1;i<=n;++i){
			Add_Tube(s,i,1,-a[i]);
			Add_Tube(i+n,t,1,-b[i]);
			Add_Tube(i,i+n,1,0);
			Add_Tube(i,ts,inf,0);
			Add_Tube(tt,i+n,inf,0);
		}
		Add_Tube(ts,tt,k-l,0);
		reg int x=2*n+4;
		Add_Tube(t,x,k,0);
		dinic(s,x);
		printf("%lld\n",-cost);
	}
	return 0;
}