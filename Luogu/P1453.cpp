#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n;
int p[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
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

pair<int,int> e;
int f[MAXN][2];

inline void dfs(reg int u,reg int father){
	f[u][0]=0,f[u][1]=p[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			f[u][0]+=max(f[v][0],f[v][1]);
			f[u][1]+=f[v][0];
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&p[i]);
	UnionFind::Init(n);
	for(reg int i=1;i<=n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		++u,++v;
		if(!UnionFind::search(u,v))
			Add_Edge(u,v),Add_Edge(v,u),UnionFind::merge(u,v);
		else
			e=make_pair(u,v);
	}
	double k;
	scanf("%lf",&k);
	int ans=0;
	dfs(e.first,e.first);
	ans=max(ans,f[e.first][0]);
	dfs(e.second,e.second);
	ans=max(ans,f[e.second][0]);
	printf("%.1lf\n",ans*k);
	return 0;
}