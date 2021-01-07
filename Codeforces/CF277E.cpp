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

const int MAXN=400+5;
const int MAXV=2*MAXN;
const int MAXE=2*(MAXN*2+MAXN*MAXN/2);
const int inf=0x3f3f3f3f;
const double eps=1e-7;

int n;
int x[MAXN],y[MAXN];

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(reg int i,reg int j){
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
double p[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg double val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg double val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXV];
double dis[MAXV];
queue<int> Q;

inline bool spfa(reg int s,reg int t){
	fill(dis,dis+t+1,1e20);
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]){
				dis[v]=dis[u]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[t]<1e20;
}

double cost;
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
		if(fabs(dis[v]-(dis[u]+p[i]))<eps&&w[i]&&!vis[v]){
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

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i){
		Add_Tube(s,i,2,0);
		Add_Tube(i+n,t,1,0);
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(y[i]>y[j])
				Add_Tube(i,j+n,1,getDis(i,j));
	reg int flow=dinic(s,t);
	if(flow==n-1)
		printf("%lf\n",cost);
	else
		puts("-1");
	return 0;
}