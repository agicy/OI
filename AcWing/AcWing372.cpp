#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=100+5;
const int MAXV=MAXN*MAXN;
const int MAXE=(MAXV+4*MAXN*MAXN)*2;
const int inf=0x3f3f3f3f;

int n,t;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(int u,int v,int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
queue<int> Q;

inline bool bfs(int s,int t){
	memset(dep,-1,sizeof(dep));
	dep[s]=0,Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int dfs(int u,int t,int lim){
	if(u==t)
		return lim;
	int flow=0;
	for(int &i=cur[u];i;i=Next[i]){
		int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int dinic(int s,int t){
	int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

bool M[MAXN][MAXN];
int id[MAXN][MAXN];

int main(void){
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		M[x][y]=true;
	}
	int tot=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			id[i][j]=++tot;
	int s=0,t=n*n+1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(!M[i][j]){
				if((i+j)&1){
					Add_Tube(s,id[i][j],1);
					const int dx[]={-1,0,0,1};
					const int dy[]={0,-1,1,0};
					for(int k=0;k<4;++k){
						int fx=i+dx[k],fy=j+dy[k];
						if(1<=fx&&fx<=n&&1<=fy&&fy<=n&&!M[fx][fy])
							Add_Tube(id[i][j],id[fx][fy],1);
					}
				}
				else
					Add_Tube(id[i][j],t,1);
			}
	printf("%d\n",dinic(s,t));
	return 0;
}