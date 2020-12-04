#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXV=MAXN;
const int MAXE=MAXN*MAXN*2;

int n;
int g[MAXN][MAXN];

int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

int W[MAXE];
bool vis[MAXV];

inline void DFS(reg int ID){
	vis[ID]=true;
	for(reg int i=head[ID];i;i=Next[i])
		if(!vis[to[i]]&&w[i]>0)
			DFS(to[i]);
	return;
}

namespace Tree{
	int cnt,head[MAXV],to[MAXV<<1],w[MAXV<<1],Next[MAXV<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,len);
		return;
	}
	int dis[MAXV][MAXV];
	inline void DFS(reg int ID,reg int father,reg int root){
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]!=father){
				dis[root][to[i]]=min(dis[root][ID],w[i]);
				DFS(to[i],ID,root);
			}
		return;
	}
	inline void GetAns(void){
		for(reg int i=1;i<=n;++i){
			dis[i][i]=INF;
			DFS(i,0,i);
		}
		for(reg int i=1;i<=n;++i)
			dis[i][i]=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				printf("%d%c",dis[i][j],j==n?'\n':' ');
		return;
	}
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
}

int fa[MAXV];

inline void Init(void){
	cnt=1;
	memset(head,0,sizeof(head));
	Tree::Init();
	return;
}

inline void Solve(reg int id){
	printf("Case #%d:\n",id);
	Init();
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			g[i][j]=read();
			Add_Tube(i,j,g[i][j]);
		}
	for(reg int j=1;j<=cnt;++j)
		W[j]=w[j];
	for(reg int i=2;i<=n;++i)
		fa[i]=1;
	for(reg int i=2;i<=n;++i){
		for(reg int j=1;j<=cnt;++j)
			w[j]=W[j];
		reg int s=i,t=fa[i];
		int res=Dinic(s,t);
		Tree::Add_Tube(s,t,res);
		memset(vis,false,sizeof(vis));
		DFS(s);
		for(reg int j=i;j<=n;++j)
			if(fa[j]==t&&vis[j])
				fa[j]=s;
	}
	Tree::GetAns();
	return;
}

int main(void){
	reg int T=read();
	for(reg int i=1;i<=T;++i)
		Solve(i);
	return 0;
}