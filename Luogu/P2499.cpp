#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXK=500+5;
const int MAXV=MAXK*2;
const int MAXE=(MAXK*2+MAXK*MAXK)*2;

int n,m,k,a,b;
char M[MAXN][MAXM];
int sx[MAXK],sy[MAXK],ex[MAXK],ey[MAXK];
queue<int> Qx,Qy;
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
	memset(dis,0X3F,sizeof(dis));
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]>0){
				dis[v]=dis[u]+p[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[t]!=INF;
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
	n=read(),m=read(),k=read(),a=read(),b=read();
	const int dx[]={-a,-a,-b,-b,b,b,a,a};
	const int dy[]={-b,b,-a,a,-a,a,-b,b};
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	for(reg int i=1;i<=k;++i)
		sx[i]=read(),sy[i]=read();
	for(reg int i=1;i<=k;++i)
		ex[i]=read(),ey[i]=read();
	for(reg int i=1;i<=k;++i){
		static bool vis[MAXN][MAXM];
		static int dis[MAXN][MAXM];
		memset(vis,false,sizeof(vis));
		vis[sx[i]][sy[i]]=true,dis[sx[i]][sy[i]]=0,Qx.push(sx[i]),Qy.push(sy[i]);
		while(!Qx.empty()){
			reg int x=Qx.front(),y=Qy.front();
			Qx.pop(),Qy.pop();
			for(reg int j=0;j<8;++j){
				int fx=x+dx[j],fy=y+dy[j];
				if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!vis[fx][fy]&&M[fx][fy]!='*'){
					vis[fx][fy]=true;
					dis[fx][fy]=dis[x][y]+1;
					Qx.push(fx),Qy.push(fy);
				}
			}
		}
		for(reg int j=1;j<=k;++j)
			if(vis[ex[j]][ey[j]])
				Add_Tube(i,j+k,1,dis[ex[j]][ey[j]]);
	}
	reg int s=0,t=2*k+1;
	for(reg int i=1;i<=k;++i){
		Add_Tube(s,i,1,0);
		Add_Tube(i+k,t,1,0);
	}
	Dinic(s,t);
	printf("%d\n",Cost);
	return 0;
}