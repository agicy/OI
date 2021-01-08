#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=1.5e3+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

namespace Network{
	const int MAXV=2*MAXN;
	const int MAXE=2*(MAXN*2+MAXN*MAXN);
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	ll w[MAXE];
	inline void Init(void){
		cnt=1,memset(head,0,sizeof(head));
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg ll len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
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
		reg int head_=0,tail_=0;
		memset(dep,-1,sizeof(dep));
		dep[s]=1,Q[tail_++]=s;
		while(head_<tail_){
			reg int u=Q[head_++];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q[tail_++]=v;
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
}

int n,m;
ll s[MAXN],p[MAXN];
ll G[MAXN][MAXN];

inline bool check(reg ll mid){
	Network::Init();
	reg int S=0,T=2*n+1;
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		sum+=s[i];
		Network::Add_Tube(S,i,s[i]),Network::Add_Tube(i+n,T,p[i]);
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(G[i][j]<=mid)
				Network::Add_Tube(i,j+n,inf);
	return sum<=Network::dinic(S,T);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		s[i]=readll(),p[i]=readll();
	memset(G,0x3f,sizeof(G));
	for(reg int i=1;i<=n;++i)
		G[i][i]=0;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		static ll w;
		u=read(),v=read(),w=readll();
		G[u][v]=G[v][u]=min(G[u][v],w);
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				if(G[i][j]>G[i][k]+G[k][j])
					G[i][j]=G[i][k]+G[k][j];
	reg ll l=0,r=inf-1,mid;
	if(!check(inf-1))
		puts("-1");
	else{
		while(l<r){
			mid=(l+r)>>1;
			if(check(mid))
				r=mid;
			else
				l=mid+1;
		}
		printf("%lld\n",l);
	}
	return 0;
}