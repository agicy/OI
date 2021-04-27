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

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(reg double x1,reg double y1,reg double x2,reg double y2){
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

const int MAXN=100+5;
const int MAXV=MAXN*2;
const int MAXE=(MAXN*MAXN+2*MAXN)*2;
const double eps=1e-6;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
double p[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg double val){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len,p[cnt]=val;
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

inline bool spfa(int s,reg int t){
	const double inf=1.0/0.0;
	fill(dis+s,dis+t+1,inf);
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
	const int inf=0x3f3f3f3f;
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int n;
int x[MAXN],y[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i){
		Add_Tube(s,i,1,0);
		Add_Tube(i+n,t,1,0);
		Add_Tube(i,i+n,1,fabs(x[i]));
		for(reg int j=1;j<=n;++j)
			if(i!=j)
				Add_Tube(i,j+n,1,0.5*getDis(-x[i],y[i],x[j],y[j]));
	}
	dinic(s,t);
	printf("%.7lf\n",cost);
	return 0;
}