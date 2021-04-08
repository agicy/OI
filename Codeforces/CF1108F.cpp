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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXLOG2N=18+1;

struct Edge{
	int u,v,w;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

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
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int Max[MAXN][MAXLOG2N];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;(1<<i)<=dep[u];++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		Max[u][i]=max(Max[u][i-1],Max[fa[u][i-1]][i-1]);
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			Max[v][0]=w[i];
			dfs(v,u);
		}
	}
	return;
}

inline pair<int,int> LCA(int x,int y){
	reg int res=0;
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x]){
			res=max(res,Max[y][i]);
			y=fa[y][i];
		}
	if(x==y)
		return make_pair(x,res);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			res=max(res,max(Max[x][i],Max[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	return make_pair(fa[x][0],max(res,max(Max[x][0],Max[y][0])));
}

Edge E[MAXM];
bool tag[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		E[i].u=read(),E[i].v=read(),E[i].w=read();
	sort(E+1,E+m+1);
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			tag[i]=true;
			Add_Edge(E[i].u,E[i].v,E[i].w),Add_Edge(E[i].v,E[i].u,E[i].w);
			UnionFind::merge(E[i].u,E[i].v);
		}
	dfs(1,0);
	reg ll ans=0;
	for(reg int i=1;i<=m;++i)
		if(!tag[i]){
			reg int val=LCA(E[i].u,E[i].v).second;
			ans+=max(val+1-E[i].w,0);
		}
	printf("%lld\n",ans);
	return 0;
}