#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define eps 1e-8
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXV=MAXN*2+5;
const int MAXE=(MAXN*MAXN+MAXN*2)*2;

int n;
int a[MAXN][MAXN];
int b[MAXN][MAXN];

int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
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

inline bool SPFA(int s,reg int t){
	for(reg int i=s;i<=t;++i)
		dis[i]=-INF;
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int id=Q.front();
		Q.pop();
		inque[id]=false;
		for(reg int i=head[id];i;i=Next[i]){
			int v=to[i];
			if(dis[v]<dis[id]+p[i]&&w[i]){
				dis[v]=dis[id]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return fabs(dis[t]+INF)>eps;
}

bool vis[MAXV];
int cur[MAXV];
double MaxCost;

inline int DFS(reg int u,reg int t,reg int lim){
	if(u==t){
		MaxCost+=dis[t]*lim;
		return lim;
	}
	vis[u]=true;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
			reg int f=DFS(v,t,min(lim-flow,w[i]));
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

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	MaxCost=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline bool check(reg double C){
	cnt=1,memset(head,0,sizeof(head));
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i){
		Add_Tube(s,i,1,0.0);
		Add_Tube(i+n,t,1,0.0);
		for(reg int j=1;j<=n;++j)
			Add_Tube(i,j+n,1,a[i][j]-b[i][j]*C);
	}
	Dinic(s,t);
	return MaxCost>=0;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			a[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			b[i][j]=read();
	reg double l=0,r=1e5,mid;
	while(fabs(r-l)>eps){
		mid=(l+r)*0.5;
		if(check(mid)){
			l=mid;
		}
		else
			r=mid;
	}
	printf("%.6lf\n",l);
	return 0;
}