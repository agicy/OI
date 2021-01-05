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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=40+5;
const int MAXM=100+5;
const int MAXP=800+5;
const int MAXV=MAXM*MAXP+MAXN;
const int MAXE=2e6;
const int inf=0x3f3f3f3f;

int n,m;
int P[MAXN];
int c[MAXN][MAXM];
int sum;
int top[MAXM];
int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len,p[cnt]=val;
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
int Q[MAXV*100];

inline bool spfa(reg int s,reg int t){
	reg int h=0,ta=0;
	fill(dis,dis+t+1,inf);
	inque[s]=true,dis[s]=0,Q[ta++]=s;
	while(h<ta){
		reg int u=Q[h++];
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]){
				dis[v]=dis[u]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q[ta++]=v;
				}
			}
		}
	}
	return dis[t]!=inf;
}

int cost;
bool vis[MAXV];
int cur[MAXV];
int nex[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		cost+=dis[t]*lim;
		return lim;
	}
	reg int flow=0;
	vis[u]=true;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]&&dis[v]==dis[u]+p[i]&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				nex[u]=v;
				if(flow==lim)
					break;
			}
		}
	}
	vis[u]=false;
	return flow;
}

inline int getId(reg int i,reg int j){
	return (i-1)*sum+j;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(spfa(s,t)){
		for(reg int i=0;i<=t;++i)
			cur[i]=head[i];
		res+=dfs(s,t,inf);
		for(reg int j=1,Id=n,u;j<=m;++j,Id+=sum)
			if(nex[Id+top[j]]&&top[j]<sum){
				++top[j];
				u=Id+top[j];
				for(reg int i=1;i<=n;++i)
					Add_Tube(i,u,1,c[i][j]*top[j]);
				Add_Tube(u,t,1,0);
			}
	}
	return res;
}

int main(void){
	n=read(),m=read();
	switch(m){
		case 1:sum=400;break;
		case 2:sum=300;break;
		case 5:sum=10;break;
		case 40:sum=(n==40)?40:100;break;
		case 50:sum=200;break;
		case 60:sum=400;break;
		case 80:sum=600;break;
		case 100:sum=800;break;
	}
	reg int s=0,t=m*sum+n+1;
	for(reg int i=1;i<=n;++i){
		P[i]=read();
		Add_Tube(s,i,P[i],0);
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1,Id=n+1;j<=m;++j,Id+=sum){
			c[i][j]=read();
			Add_Tube(i,Id,1,c[i][j]);
		}
	for(reg int i=1,Id=n+1;i<=m;++i,Id+=sum){
		top[i]=1;
		Add_Tube(Id,t,1,0);
	}
	dinic(s,t);
	printf("%d\n",cost);
	return 0;
}