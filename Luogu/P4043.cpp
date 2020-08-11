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

const int MAXN=300+5;
const int MAXV=MAXN;
const int MAXK=5e3+5;
const int MAXE=(MAXK+MAXN*2)*2;
const int inf=0x3f3f3f3f;

int n;
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

bool inque[MAXV];
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
			if(w[i]&&dis[v]>dis[u]+p[i]){
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

int cost;
bool vis[MAXV];
int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		cost+=dis[t]*lim;
		return lim;
	}
	vis[u]=true;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(w[i]&&!vis[v]&&dis[v]==dis[u]+p[i]){
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
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int deg[MAXV];

int main(void){
	n=read();
	reg int s=1,t=n+1;
	reg int S=0,T=n+2;
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		static int k;
		k=read();
		for(reg int j=1;j<=k;++j){
			static int b,t;
			b=read(),t=read();
			--deg[i],++deg[b];
			ans+=t;
			Add_Tube(i,b,inf,t);
		}
	}
	for(reg int i=2;i<=n;++i)
		Add_Tube(i,t,inf,0);
	for(reg int i=1;i<=n;++i){
		if(deg[i]>0)
			Add_Tube(S,i,deg[i],0);
		if(deg[i]<0)
			Add_Tube(i,T,-deg[i],0);
	}
	Add_Tube(t,s,inf,0);
	dinic(S,T);
	printf("%d\n",ans+cost);
	return 0;
}