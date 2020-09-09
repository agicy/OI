#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=20+5;
const int inf=0x3f3f3f3f;

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

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m,k;
Edge E[MAXN];
vector<Edge> Ea;
bool vis[MAXN][MAXN];
int g[MAXN][MAXN];
int out[MAXN],dis[MAXN];
map<string,int> M;

inline void dfs(reg int u){
	for(reg int i=2;i<=n;++i)
		if(E[i].v==0&&g[u][i]&&vis[u][i]){
			if(E[u].w>g[u][i])
				E[i]=E[u];
			else
				E[i]=Edge(u,i,g[u][i]);
			dfs(i);
		}
	return;
}

int main(void){
	memset(g,0x3f,sizeof(g));memset(dis,0x3f,sizeof(dis));
	n=1,M["Park"]=1;
	cin>>m;
	for(reg int i=1;i<=m;++i){
		static string a,b;
		static int w;
		cin>>a>>b>>w;
		if(!M[a])
			M[a]=++n;
		if(!M[b])
			M[b]=++n;
		reg int pa=M[a],pb=M[b];
		g[pa][pb]=g[pb][pa]=min(g[pa][pb],w);
		Ea.push_back(Edge(pa,pb,w));
	}
	reg ll ans=0;
	UnionFind::Init(n);
	sort(Ea.begin(),Ea.end());
	for(vector<Edge>::iterator it=Ea.begin();it!=Ea.end();++it)
		if(it->u!=1&&it->v!=1&&!UnionFind::search(it->u,it->v)){
			vis[it->u][it->v]=vis[it->v][it->u]=1;
			ans+=it->w;
			UnionFind::merge(it->u,it->v);
		}
	cin>>k;
	for(reg int i=2;i<=n;++i)
		if(g[1][i]!=inf){
			reg int rt=UnionFind::find(i);
			if(dis[rt]>g[1][i]){
				dis[rt]=g[1][i];
				out[rt]=i;
			}
		}
	for(reg int i=1;i<=n;++i)
		if(dis[i]!=inf){
			--k;
			ans+=dis[i];
			vis[1][out[i]]=vis[out[i]][1]=1;
		}
	while(k--){
		memset(E,0,sizeof(E));
		dfs(1);
		reg ll cur=0,v=0;
		for(reg int i=2;i<=n;++i)
			if(g[1][i]&&!vis[1][i]&&E[i].w-g[1][i]>cur){
				cur=E[i].w-g[1][i];
				v=i;
			}
		if(cur<=0)
			break;
		ans-=cur;
		vis[E[v].u][E[v].v]=vis[E[v].v][E[v].u]=false;
		vis[1][v]=vis[v][1]=true;
	}
	printf("Total miles driven: %lld\n",ans);
	return 0;
}