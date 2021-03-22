#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0)	x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=5e4+5;
const int MAXM=1e6+5;
const int MAXLOG2N=16+1;
const int MAXV=MAXN+MAXN*MAXLOG2N*2+MAXM;
const int inf=0x3f3f3f3f;

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

struct updates{
	int u1,v1,u2,v2,w;
	inline updates(reg int u1=0,reg int v1=0,reg int u2=0,reg int v2=0,reg int w=0):u1(u1),v1(v1),u2(u2),v2(v2),w(w){
		return;
	}
};

int n,m,s;
int lg[MAXN];
int cnt,tot;
updates u[MAXM];
vector<int> G[MAXN];
vector<Edge> Gp[MAXV];

inline void Add_Edge(reg int u,reg int v,reg int w){
	Gp[u].push_back(Edge(v,w));
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int id[MAXN][MAXLOG2N][2];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	id[u][0][0]=id[u][0][1]=u;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=1;(1<<i)<=dep[u];++i){
		id[u][i][0]=++tot,id[u][i][1]=++tot;
		Add_Edge(id[u][i-1][0],id[u][i][0],0);
		Add_Edge(id[fa[u][i-1]][i-1][0],id[u][i][0],0);
		Add_Edge(id[u][i][1],id[u][i-1][1],0);
		Add_Edge(id[u][i][1],id[fa[u][i-1]][i-1][1],0);
	}
	for(int v:G[u])
		if(v!=father)
			dfs(v,u);
	return;
}

inline int getFa(reg int u,reg int k){
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if((k>>i)&1)
			u=fa[u][i];
	return u;
}

inline void build(reg int u,reg int v,reg int w,reg int type){
	reg int j=0;
	while((1<<(j+1))<=dep[u]-dep[v]+1)
		++j;
	reg int fa=getFa(u,dep[u]-dep[v]+1-(1<<j));
	if(type){
		Add_Edge(tot,id[u][j][type],w);
		Add_Edge(tot,id[fa][j][type],w);
	}
	else{
		Add_Edge(id[u][j][type],tot,w);
		Add_Edge(id[fa][j][type],tot,w);
	}
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	y=getFa(y,dep[y]-dep[x]);
	if(x==y)
		return x;
	for(reg int i=lg[dep[x]];i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

struct Node{
	int id,dis;
	inline Node(reg int id=0,reg int dis=0):id(id),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

int dis[MAXV];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(s.dis>dis[u])
			continue;
		for(Edge e:Gp[u])
			if(dis[e.v]>dis[u]+e.w){
				dis[e.v]=dis[u]+e.w;
				Q.push(Node(e.v,dis[e.v]));
			}
	}
	return;
}

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int main(void){
	n=read(),m=read(),s=read();
	UnionFind::Init(n);
	for(reg int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(reg int i=1;i<=m;++i)
		switch(read()){
			case 1:{
				static int u1,v1,u2,v2,w;
				u1=read(),v1=read(),u2=read(),v2=read(),w=read();
				if(UnionFind::search(u1,v1)&&UnionFind::search(u2,v2))
					u[++cnt]=updates(u1,v1,u2,v2,w);
				break;
			}
			case 2:{
				static int u,v,w;
				u=read(),v=read(),w=read();
				if(!UnionFind::search(u,v)){
					UnionFind::merge(u,v);
					G[u].push_back(v),G[v].push_back(u);
					Add_Edge(u,v,w),Add_Edge(v,u,w);
				}
				break;
			}
		}
	tot=n+1;
	for(reg int i=1;i<=n;++i)
		if(!dep[i])
			dfs(i,0);
	for(reg int i=1;i<=cnt;++i){
		reg int p1=LCA(u[i].u1,u[i].v1),p2=LCA(u[i].u2,u[i].v2);
		++tot;
		build(u[i].u1,p1,0,0),build(u[i].v1,p1,0,0),build(u[i].u2,p2,u[i].w,1),build(u[i].v2,p2,u[i].w,1);
	}
	dijkstra(s);
	for(reg int i=1;i<=n;++i)
		write(dis[i]==inf?-1:dis[i]),putchar(i==n?'\n':' ');
	flush();
	return 0;
}