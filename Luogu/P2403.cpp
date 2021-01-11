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

const int MAXN=1e5+5;
const int MAXR=1e6+5;
const int MAXC=1e6+5;

int n,r,c;
map<pair<int,int>,int> M;
vector<int> Vx[MAXR],Vy[MAXC];
vector<int> Zx[MAXR],Zy[MAXC];

namespace Graph{
	const int MAXV=MAXN;
	const int MAXE=9*MAXN;
	inline int min(reg int a,reg int b){
		return a<b?a:b;
	}
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	bool vis[MAXV];
	int tim,dfn[MAXV],low[MAXV];
	int top,S[MAXV];
	int scc_cnt,col[MAXV],siz[MAXV];
	inline void tarjan(reg int u){
		vis[u]=true;
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!dfn[v]){
				tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(vis[v])
				low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u]){
			++scc_cnt;
			reg int v;
			do{
				v=S[top--];
				vis[v]=false;
				col[v]=scc_cnt;
				++siz[scc_cnt];
			}while(u!=v);
		}
		return;
	}
}

namespace DAG{
	const int MAXV=MAXN;
	const int MAXE=9*MAXN;
	inline int max(reg int a,reg int b){
		return a>b?a:b;
	}
	int indeg[MAXV];
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		++indeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int f[MAXV];
	int Q[MAXV];
	inline int topo(reg int n){
		reg int head_=0,tail_=0;
		for(reg int i=1;i<=n;++i)
			if(!indeg[i]){
				f[i]=Graph::siz[i];
				Q[tail_++]=i;
			}
		reg int res=0;
		while(head_<tail_){
			reg int u=Q[head_++];
			res=max(res,f[u]);
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				f[v]=max(f[v],f[u]+Graph::siz[v]);
				--indeg[v];
				if(!indeg[v])
					Q[tail_++]=v;
			}
		}
		return res;
	}
}

struct Point{
	int id,x,y;
	inline Point(reg int id=0,reg int x=0,reg int y=0):id(id),x(x),y(y){
		return;
	}
};

vector<Point> V;
bool visX[MAXR],visY[MAXC];
int X[MAXN],totX;
int Y[MAXN],totY;

int main(void){
	n=read(),r=read(),c=read();
	for(int i=1;i<=n;++i){
		static int x,y,t;
		x=read(),y=read(),t=read();
		switch(t){
			case 1:{
				Vx[x].push_back(i),Zy[y].push_back(i);
				if(!visX[x])
					visX[x]=true,X[++totX]=x;
				break;
			}
			case 2:{
				Vy[y].push_back(i),Zx[x].push_back(i);
				if(!visY[y])
					visY[y]=true,Y[++totY]=y;
				break;
			}
			case 3:{
				Zx[x].push_back(i),Zy[y].push_back(i);
				V.push_back(Point(i,x,y));
				break;
			}
		}
		M[make_pair(x,y)]=i;
	}
	for(reg int i=0,siz=V.size();i<siz;++i){
		reg int x=V[i].x,y=V[i].y;
		const int dx[]={-1,-1,-1,0,0,1,1,1};
		const int dy[]={-1,0,1,-1,1,-1,0,1};
		for(reg int k=0;k<8;++k)
			if(M.find(make_pair(x+dx[k],y+dy[k]))!=M.end())
				Graph::Add_Edge(V[i].id,M.find(make_pair(x+dx[k],y+dy[k]))->second);
	}
	for(reg int i=1,ptr,j,u,siz;i<=totX&&(ptr=X[i]);++i){
		for(j=1,siz=Vx[ptr].size();j<siz;++j)
			Graph::Add_Edge(Vx[ptr][j],Vx[ptr][j-1]);
		u=Vx[ptr][0];
		Graph::Add_Edge(u,Vx[ptr][Vx[ptr].size()-1]);
		for(int x:Zx[ptr])
			Graph::Add_Edge(u,x);
	}
	for(reg int i=1,ptr,j,u,siz;i<=totY&&(ptr=Y[i]);++i){
		for(j=1,siz=Vy[ptr].size();j<siz;++j)
			Graph::Add_Edge(Vy[ptr][j],Vy[ptr][j-1]);
		u=Vy[ptr][0];
		Graph::Add_Edge(u,Vy[ptr][Vy[ptr].size()-1]);
		for(int x:Zy[ptr])
			Graph::Add_Edge(u,x);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int u=1,i,v;u<=n;++u)
		for(i=Graph::head[u];i&&(v=Graph::to[i]);i=Graph::Next[i])
			if(Graph::col[u]!=Graph::col[v])
				DAG::Add_Edge(Graph::col[u],Graph::col[v]);
	reg int ans=DAG::topo(Graph::scc_cnt);
	printf("%d\n",ans);
	return 0;
}