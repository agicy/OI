#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool fa=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)fa|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return fa?-res:res;
}

const int MAXN=400000+5;
const int MAXM=800000+5;
const int MAXLOG2N=20+1;

inline void Read(void);
inline void Work(void);
inline void Init(void);

int main(void){
	reg int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

namespace Graph{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	struct Node{
		int ID,dis;
		inline Node(reg int ID=0,reg int dis=0):ID(ID),dis(dis){
			return;
		}
		inline bool operator<(const Node& a)const{
			return dis<a.dis;
		}
		inline bool operator>(const Node& a)const{
			return dis>a.dis;
		}
	};
	bool vis[MAXN];
	int dis[MAXN];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void Dijkstra(reg int s){
		memset(vis,false,sizeof(vis));
		memset(dis,0X3F,sizeof(dis));
		while(!Q.empty())Q.pop();
		dis[s]=0,Q.push(Node(s,0));
		while(!Q.empty()){
			reg int ID=Q.top().ID;
			Q.pop();
			if(vis[ID])
				continue;
			vis[ID]=true;
			for(reg int i=head[ID];i;i=Next[i])
				if(dis[to[i]]>dis[ID]+w[i]){
					dis[to[i]]=dis[ID]+w[i];
					Q.push(Node(to[i],dis[to[i]]));
				}
		}
		return;
	}
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
}

struct Edge{
	int u,v,l,w;
	inline void Read(void){
		u=read(),v=read(),l=read(),w=read();
		return;
	}
};

inline bool cmp(Edge a,Edge b){
	return a.w>b.w;
}

int n,m;
Edge E[MAXM],p[MAXN<<1];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		E[i].Read();
		Graph::Add_Edge(E[i].u,E[i].v,E[i].l);
		Graph::Add_Edge(E[i].v,E[i].u,E[i].l);
	}
	return;
}

namespace Tree{
	int V;
	int cnt,head[MAXN<<1],to[MAXN<<2],Next[MAXN<<2];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int dep[MAXN],fa[MAXN][MAXLOG2N];
	inline void DFS(reg int ID,reg int father){
		dep[ID]=dep[father]+1;
		fa[ID][0]=father;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[ID][i]=fa[fa[ID][i-1]][i-1];
		for(reg int i=head[ID];i;i=Next[i]){
			DFS(to[i],ID);
			p[ID].l=min(p[ID].l,p[to[i]].l);
		}
		return;
	}
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		memset(fa,0,sizeof(fa));
		return;
	}
	inline int Query(reg int x,reg int y){
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[x][i]!=0&&p[fa[x][i]].w>y)
				x=fa[x][i];
		return p[x].l;
	}
}

struct UnionFind{
	int ID[MAXN<<1];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

UnionFind S;

inline void Kruskal(void){
	Tree::V=n;
	S.Init(n<<1);
	sort(E+1,E+m+1,cmp);
	reg int tot=0;
	for(reg int i=1;i<=m&&tot<n-1;++i)
		if(!S.search(E[i].u,E[i].v)){
			reg int fx=S.find(E[i].u),fy=S.find(E[i].v);
			reg int ID=++Tree::V;
			Tree::Add_Edge(ID,fx);
			Tree::Add_Edge(ID,fy);
			S.ID[fx]=S.ID[fy]=ID;
			p[ID].w=E[i].w;
			++tot;
		}
	return;
}

inline void Work(void){
	for(reg int i=n+1;i<=(n<<1);++i)
		p[i].l=INF;
	Graph::Dijkstra(1);
	for(reg int i=1;i<=n;++i)
		p[i].l=Graph::dis[i];
	reg int Q=read(),K=read(),_S=read();
	Kruskal();
	Tree::DFS(Tree::V,0);
	reg int lastans=0;
	while(Q--){
		static int x,y;
		x=read(),y=read();
		x=(x+K*lastans-1)%n+1,y=(y+K*lastans)%(_S+1);
		reg int ans=Tree::Query(x,y);
		printf("%d\n",ans);
		lastans=ans;
	}
	return;
}

inline void Init(void){
	memset(E,0,sizeof(E));
	Tree::Init();
	Graph::Init();
	return;
}