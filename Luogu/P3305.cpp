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

const int MAXN=100+5;
const int MAXM=1e3+5;
const double eps=1e-8;
const double inf=1e7;

namespace Network{
	const int MAXV=MAXN;
	const int MAXE=2*MAXM;
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	double w[MAXE];
	inline void Init(void){
		cnt=1,memset(head,0,sizeof(head));
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg double len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg double len){
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
				if(dep[v]==-1&&w[i]>eps){
					dep[v]=dep[u]+1;
					Q[tail_++]=v;
				}
			}
		}
		return dep[t]!=-1;
	}
	int cur[MAXV];
	inline double dfs(reg int u,reg int t,reg double lim){
		if(u==t)
			return lim;
		reg double flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]>eps){
				reg double f=dfs(v,t,min(lim-flow,w[i]));
				if(f>eps){
					flow+=f;
					w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		return flow;
	}
	inline double dinic(reg int s,reg int t){
		reg double res=0;
		while(bfs(s,t)){
			memcpy(cur,head,sizeof(head));
			res+=dfs(s,t,inf);
		}
		return res;
	}
}

int n,m,p;
int a[MAXM],b[MAXM],c[MAXM];
double ans;

inline bool check(reg double mid){
	Network::Init();
	for(reg int i=1;i<=m;++i)
		if(c[i]<=mid)
			Network::Add_Tube(a[i],b[i],c[i]);
		else
			Network::Add_Tube(a[i],b[i],mid);
	reg double flow=Network::dinic(1,n);
	return fabs(ans-flow)<eps;
}

int main(void){
	n=read(),m=read(),p=read();
	Network::Init();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),c[i]=read();
		Network::Add_Tube(a[i],b[i],c[i]);
	}
	ans=Network::dinic(1,n);
	reg double l=0,r=5e4,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.0lf\n%lf\n",ans,l*p);
	return 0;
}