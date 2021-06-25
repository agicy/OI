#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

const int MAXN=80+5;
const int MAXM=80+5;
const int MAXP=80+5;
const int MAXY=1e3+5;
const double eps=1e-6;
const double inf=1e20;

namespace Network{
	const int MAXV=MAXN*(MAXM+1);
	const int MAXE=(MAXN*2+MAXN*MAXM+MAXY*MAXM)*2;
	int cnt,head[MAXV],to[MAXE],nxt[MAXE];
	double w[MAXE];
	inline void init(reg int s,reg int t){
		cnt=1,fill(head+s,head+t+1,0);
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg double lim){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=lim;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg double lim){
		Add_Edge(u,v,lim);
		Add_Edge(v,u,0);
		return;
	}
	int dep[MAXV];
	int cur[MAXV];
	inline bool bfs(reg int s,reg int t){
		fill(dep+s,dep+t+1,-1);
		reg int _head=0,_tail=0;
		static int Q[MAXV];
		dep[s]=1,Q[_tail++]=s;
		while(_head<_tail){
			reg int u=Q[_head++];
			cur[u]=head[u];
			for(reg int i=head[u];i;i=nxt[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]>eps)
					dep[v]=dep[u]+1,Q[_tail++]=v;
			}
		}
		return dep[t]!=-1;
	}
	inline double dfs(reg int u,reg int t,reg double lim){
		if(u==t)
			return lim;
		reg double flow=0;
		for(reg int &i=cur[u];i;i=nxt[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]>eps){
				reg double f=dfs(v,t,min(lim-flow,w[i]));
				if(f>eps){
					flow+=f,w[i]-=f,w[i^1]+=f;
					if(fabs(flow-lim)<eps)
						break;
				}
			}
		}
		return flow;
	}
	inline double dinic(reg int s,reg int t){
		reg double flow=0;
		while(bfs(s,t)){
			flow+=dfs(s,t,inf);
			if(flow>=inf)
				return inf;
		}
		return flow;
	}
}

int n,m,p,y;
int c[MAXP];
double val[MAXN][MAXM];

inline int getId(reg int i,reg int j){
	return (i-1)*(m+1)+j;
}

bool ed;

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&n,&m,&p,&y);
		for(reg int i=1;i<=p;++i)
			scanf("%d",&c[i]);
		for(reg int i=1;i<=m;++i)
			for(reg int j=1;j<=n;++j){
				reg double bas=1,sum=0;
				for(reg int k=1;k<=p;++k){
					static double x;
					scanf("%lf",&x);
					bas*=x,sum+=bas*c[k];
				}
				val[j][i]=sum;
			}
		reg int s=0,t=n*(m+1)+1;
		Network::init(s,t);
		for(reg int i=1;i<=n;++i){
			Network::Add_Tube(s,getId(i,1),inf);
			Network::Add_Tube(getId(i,m+1),t,inf);
		}
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j){
				Network::Add_Tube(getId(i,j),getId(i,j+1),val[i][j]);
				Network::Add_Tube(getId(i,j+1),getId(i,j),inf);
			}
		while(y--){
			static int i,j,k;
			scanf("%d%d%d",&i,&j,&k);
			for(reg int x=1;x<=m;++x)
				if(1<=x+k&&x+k<=m+1)
					Network::Add_Tube(getId(j,x),getId(i,x+k),inf);
		}
		reg double res=Network::dinic(s,t);
		if(res>=inf)
			puts("-1");
		else
			printf("%.4lf\n",res);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}