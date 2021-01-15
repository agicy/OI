#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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
const int MAXA=1e3+5;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=MAXN*MAXN/2+MAXA;
	const int MAXE=2*(MAXN*MAXN/2*3);
	int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len){
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
	inline int dfs(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
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
	inline int dinic(reg int s,reg int t){
		reg int res=0;
		while(bfs(s,t)){
			memcpy(cur,head,sizeof(head));
			res+=dfs(s,t,inf);
		}
		return res;
	}
}

int n,m;
int a[MAXN];
int f[MAXN][MAXN];
int id[MAXN][MAXN];

int main(void){
	n=read(),m=read();
	int Max=0;
	for(reg int i=1;i<=n;++i)
		Max=max(Max,a[i]=read());
	reg int s=0,t=(n+1)*n/2+Max+1;
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;++j){
			f[i][j]=read();
			id[i][j]=++tot;
		}
	reg int sum=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;++j){
			reg int cost=f[i][j];
			if(i==j){
				if(m)
					Network::Add_Tube(id[i][j],tot+a[i],inf);
				cost-=a[i];
			}
			else{
				Network::Add_Tube(id[i][j],id[i+1][j],inf);
				Network::Add_Tube(id[i][j],id[i][j-1],inf);
			}
			if(cost>0)
				sum+=cost,Network::Add_Tube(s,id[i][j],cost);
			if(cost<0)
				Network::Add_Tube(id[i][j],t,-cost);
		}
	if(m)
		for(reg int i=1;i<=Max;++i)
			Network::Add_Tube(++tot,t,i*i);
	printf("%d\n",sum-Network::dinic(s,t));
	return 0;
}