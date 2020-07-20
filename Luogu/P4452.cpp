#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=200+5;
const int MAXV=2*MAXM;
const int MAXE=(MAXM*3+MAXM*MAXM)*2;

struct Node{
	int a,b,s,t,c;
	inline void Read(void){
		a=read()+1,b=read()+1,s=read(),t=read(),c=read();
		return;
	}
};

int n,m,K,T;
int tim[MAXN][MAXN];
int f[MAXN][MAXN];
Node q[MAXM];

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

inline bool SPFA(int s,reg int t){
	for(reg int i=s;i<=t;++i)
		dis[i]=-INF;
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]<dis[u]+p[i]&&w[i]>0){
				dis[v]=dis[u]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[t]!=-INF;
}

int Cost;
bool vis[MAXV];
int cur[MAXV];

inline int DFS(reg int u,reg int t,reg int lim){
	if(u==t){
		Cost+=lim*dis[t];
		return lim;
	}
	vis[u]=true;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]==dis[u]+p[i]&&w[i]>0&&!vis[v]){
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
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

int main(void){
	n=read(),m=read(),K=read(),T=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			tim[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			f[i][j]=read();
	for(reg int i=1;i<=m;++i)
		q[i].Read();
	reg int s=0,sp=2*m+1,t=2*m+2;
	for(reg int i=1;i<=m;++i){
		Add_Tube(i,i+m,1,q[i].c);
		if(q[i].t+tim[q[i].b][1]<=T)
			Add_Tube(i+m,t,INF,-f[q[i].b][1]);
		else
			continue;
		if(q[i].s>=tim[1][q[i].a])
			Add_Tube(sp,i,INF,-f[1][q[i].a]);
		for(reg int j=1;j<=m;++j)
			if(q[i].t+tim[q[i].b][q[j].a]<=q[j].s)
				Add_Tube(i+m,j,INF,-f[q[i].b][q[j].a]);
	}
	Add_Tube(s,sp,K,0);
	Dinic(s,t);
	printf("%d\n",Cost);
	return 0;
}