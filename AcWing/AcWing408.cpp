#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXV=MAXN*MAXM;
const int MAXE=(1e4+2e2)*2;
const int inf=0x3f3f3f3f;

int n,m;
char M[MAXN][MAXM];
int id[MAXN][MAXM];
int cnt,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

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

int cost;
bool vis[MAXV];
int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		cost+=lim*dis[u];
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

inline int dinic(reg int s,reg int t){
	cost=0;
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

bool bfs_vis[MAXN][MAXM];
queue<int> Qx,Qy,Qdep;

inline void getVal(int sx,int sy){
	memset(bfs_vis,false,sizeof(bfs_vis));
	Qx.push(sx),Qy.push(sy),Qdep.push(0);
	while(!Qx.empty()){
		reg int x=Qx.front(),y=Qy.front(),dep=Qdep.front();
		Qx.pop(),Qy.pop(),Qdep.pop();
		if(M[x][y]=='H')
			Add_Tube(id[sx][sy],id[x][y],1,dep);
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int k=0;k<4;++k){
			int fx=x+dx[k],fy=y+dy[k];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!bfs_vis[fx][fy]){
				bfs_vis[fx][fy]=true;
				Qx.push(fx),Qy.push(fy),Qdep.push(dep+1);
			}
		}
	}
	return;
}

int main(void){
	while(n=read(),m=read(),n||m){
		cnt=1,memset(head,0,sizeof(head));
		for(reg int i=1;i<=n;++i)
			scanf("%s",M[i]+1);
		reg int tot=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				id[i][j]=++tot;
		reg int s=0,t=n*m+1;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				switch(M[i][j]){
					case 'm':{
						Add_Tube(s,id[i][j],1,0);
						getVal(i,j);
						break;
					}
					case 'H':{
						Add_Tube(id[i][j],t,1,0);
						break;
					}
				}
		dinic(s,t);
		printf("%d\n",cost);
	}
	return 0;
}