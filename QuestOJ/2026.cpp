#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300000+5;
const int MAXM=300000+5;
const int MAXLOG2N=19+1;

int n,m;
int cnt,head[MAXM],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		Add_Edge(x,y,z);
		Add_Edge(y,x,z);
	}
	return;
}

int Time,dfn[MAXN],low[MAXN];
int top,Stack[MAXN];
int Tarjan_cnt,color[MAXN];

inline void Tarjan(reg int ID,reg int fa){
	dfn[ID]=low[ID]=++Time;
	Stack[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i]){
		if(dfn[to[i]]==0){
			Tarjan(to[i],ID);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(to[i]!=fa)
			low[ID]=min(low[ID],dfn[to[i]]);
	}
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=Stack[top--];
			color[To]=Tarjan_cnt;
		}while(To!=ID);
	}
	return;
}

struct Edge{
	int to,w;
	inline Edge(int a,int b){
		to=a,w=b;
		return;
	}
};

vector<Edge> G[MAXN];
int fa[MAXN][MAXLOG2N],dep[MAXN];
int weight[MAXN];
int dis[MAXN];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	dis[ID]+=weight[ID];
	dep[ID]=dep[father]+1;
	for(reg int i=0;i<(int)G[ID].size();++i)
		if(G[ID][i].to!=father){
			dis[G[ID][i].to]=dis[ID]+G[ID][i].w;
			DFS(G[ID][i].to,ID);
		}
	return;
}

inline void LCA_Init(void){
	for(reg int j=1;j<MAXLOG2N;++j)
		for(reg int i=1;i<=n;++i)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline void Work(void){
	Tarjan(1,0);
	for(reg int i=1;i<=n;++i)
		for(reg int j=head[i];j;j=Next[j])
			if(color[i]==color[to[j]])
				weight[color[i]]+=w[j];
			else
				G[color[i]].push_back(Edge(color[to[j]],w[j]));
	DFS(1,0);
	LCA_Init();
	reg int Q=read();
	while(Q--){
		static int u,v,lca;
		u=color[read()],v=color[read()],lca=LCA(u,v);
		puts(dis[u]+dis[v]-(dis[lca]<<1)+weight[lca]>0?"YES":"NO");
	}
	return;
}
