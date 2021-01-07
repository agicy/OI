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

const int MAXN=150+5;
const int MAXM=2e4+5;
const int MAXV=MAXN*2;
const int MAXE=2*(MAXN*MAXN/2+2*MAXN);
const int inf=0x3f3f3f3f;

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
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]){
				dis[v]=dis[u]+p[i];
				Q.push(v);
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
	reg int flow=0;
	vis[u]=true;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
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

int n,m,k;
int f[MAXN][MAXN];

int main(void){
	n=read(),m=read(),k=read();
	memset(f,0x3f,sizeof(f));
	for(reg int i=0;i<=n;++i)
		f[i][i]=0;
	for(reg int i=1;i<=m;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		f[a][b]=min(f[a][b],l);
		f[b][a]=min(f[b][a],l);
	}
	for(reg int k=0;k<=n;++k)
		for(reg int i=0;i<=n;++i)
			for(reg int j=0;j<=n;++j)
				if((k<i||k<j)&&f[i][j]>f[i][k]+f[k][j])
					f[i][j]=f[i][k]+f[k][j];
	reg int s=2*n+2,t=2*n+3;
	for(reg int i=0;i<=n;++i){
		Add_Tube(s,i,i?1:k,0),Add_Tube(i+n+1,t,1,0);
		for(reg int j=i+1;j<=n;++j)
			Add_Tube(i,j+n+1,1,f[i][j]);
	}
	dinic(s,t);
	printf("%d\n",cost);
	return 0;
}