#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X7F7F7F7F
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

const int MAXN=50000+5;
const int MAXM=50000+5;
const int MAXK=20000+5;
const int MAXLOG2K=15+1;

inline void Read(void);
inline void Work(void);
inline void Init(void);

int main(void){
	//freopen("hack.in","r",stdin);
	//freopen("hack.out","w",stdout);
	reg int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

int n,m,K;

namespace Trie{
	struct Edge{
		int to,w;
		inline Edge(reg int to=0,reg int w=0):to(to),w(w){
			return;
		}
		inline bool operator<(const Edge& a)const{
			return w<a.w;
		}
	};
	int dep[MAXK],fa[MAXK][MAXLOG2K];
	int tim,dfn[MAXK];
	vector<Edge> G[MAXK];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		G[u].push_back(Edge(v,len));
		return;
	}
	inline void DFS(reg int ID,reg int father){
		dfn[ID]=++tim;
		fa[ID][0]=father;
		dep[ID]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2K;++i){
			fa[ID][i]=fa[fa[ID][i-1]][i-1];
			if(fa[ID][i]==0)
				break;
		}
		for(reg int i=0,size=G[ID].size();i<size;++i)
			DFS(G[ID][i].to,ID);
		return;
	}
	inline void Solve(void){
		for(reg int i=1;i<=K;++i)
			sort(G[i].begin(),G[i].end());
		DFS(1,0);
		return;
	}
	inline int LCA(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2K-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x])
				y=fa[y][i];
		if(x==y)
			return x;
		for(reg int i=MAXLOG2K-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline void Init(void){
		tim=0;
		memset(fa,0,sizeof(fa));
		for(reg int i=1;i<=K;++i)
			G[i].clear();
		return;
	}
}

using Trie::dfn;
using Trie::LCA;
using Trie::dep;

namespace Graph{
	const int MAXV=4*MAXN;
	const int MAXE=20*MAXN;

	int tot,Edge_ID[MAXV];
	vector<int> E[4][MAXN];
	int s;

	inline bool cmp(reg int a,reg int b){
		return dfn[Edge_ID[a]]<dfn[Edge_ID[b]];
	}
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Edge(reg int a,reg int b,reg int c,reg int d){
		if(a==1){
			Add_Edge(s,tot+1,0);
			Add_Edge(s,tot+3,0);
		}
		for(int i=1;i<=4;++i)
			Edge_ID[tot+i]=d;
		Add_Edge(tot+1,tot+2,c);
		Add_Edge(tot+1,tot+4,c);
		Add_Edge(tot+3,tot+4,c);
		Add_Edge(tot+3,tot+2,c);
		E[0][a].push_back(++tot);
		E[1][b].push_back(++tot);
		E[2][a].push_back(++tot);
		E[3][b].push_back(++tot);
		return;
	}
	inline void Build(void){
		for(reg int ID=1;ID<=n;++ID){
			for(reg int i=0;i<4;++i)
				sort(E[i][ID].begin(),E[i][ID].end(),cmp);
			for(reg int i=0;i<4;++i)
				for(reg int j=0,size=E[i][ID].size();j<size-1;++j){
					if(i<2)
						Add_Edge(E[i][ID][j],E[i][ID][j+1],0);
					else
						Add_Edge(E[i][ID][j+1],E[i][ID][j],0);
				}
			static int temp[MAXM<<2];
			reg int size=E[0][ID].size()+E[1][ID].size();
			merge(E[1][ID].begin(),E[1][ID].end(),E[0][ID].begin(),E[0][ID].end(),temp,cmp);
			for(reg int k=0,i=0,j=0;k<size-1;++k){
				if(temp[k]&1)
					++j;
				else
					++i;
				reg int w=dep[LCA(Edge_ID[temp[k]],Edge_ID[temp[k+1]])]-1;
				if(i!=0&&j!=(int)E[0][ID].size())
					Add_Edge(E[1][ID][i-1],E[0][ID][j],w);
				if(i!=(int)E[3][ID].size()&&j!=0)
					Add_Edge(E[3][ID][i],E[2][ID][j-1],w);
			}
		}
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
	bool vis[MAXV];
	int dis[MAXV];
	priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
	inline void Dijkstra(reg int s){
		memset(vis,false,sizeof(vis));
		memset(dis,0X7F,sizeof(dis));
		while(!Q.empty())Q.pop();
		dis[s]=0,Q.push(Node(s,0));
		while(!Q.empty()){
			reg int ID=Q.top().ID;
			Q.pop();
			if(vis[ID])
				continue;
			vis[ID]=true;
			for(reg int i=head[ID];i;i=Next[i])
				if(!vis[to[i]]&&dis[to[i]]>dis[ID]+w[i]){
					dis[to[i]]=dis[ID]+w[i];
					Q.push(Node(to[i],dis[to[i]]));
				}
		}
		return;
	}
	inline void Solve(void){
		Dijkstra(s);
		for(reg int i=2;i<=n;++i){
			int ans=INF;
			for(reg int j=0,size=E[1][i].size();j<size;++j)
				ans=min(ans,dis[E[1][i][j]]);
			for(reg int j=0,size=E[3][i].size();j<size;++j)
				ans=min(ans,dis[E[3][i][j]]);
			printf("%d\n",ans);
		}
		return;
	}
	inline void Init(void){
		cnt=tot=0;
		memset(head,0,sizeof(head));
		for(reg int i=0;i<4;++i)
			for(reg int j=1;j<=n;++j)
				E[i][j].clear();
		return;
	}
}

inline void Read(void){
	n=read(),m=read(),K=read();
	Graph::s=4*m+1;
	for(reg int i=1;i<=m;++i){
		static int a,b,c,d;
		a=read(),b=read(),c=read(),d=read();
		Graph::Add_Edge(a,b,c,d);
	}
	for(reg int i=1;i<K;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Trie::Add_Edge(u,v,w);
	}
	return;
}

inline void Work(void){
	Trie::Solve();
	Graph::Build();
	Graph::Solve();
	return;
}

inline void Init(void){
	Trie::Init();
	Graph::Init();
	return;
}
