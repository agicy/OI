#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e3+5;
const int MAXLOG2N=10+1;
const int MAXM=2e3+5;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

struct edge{
	int u,v,w;
	inline bool operator<(const edge& a)const{
		return w<a.w;
	}
};

int n,m;
ll X;
edge e[MAXM];
bool tag[MAXM];
ll sum;

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
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

vector<Edge> G[MAXN];
int dep[MAXN];
int fa[MAXN][MAXLOG2N];
int Max[MAXN][MAXLOG2N];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		Max[u][i]=max(Max[u][i-1],Max[fa[u][i-1]][i-1]);
	}
	for(Edge e:G[u])
		if(e.v!=father){
			Max[e.v][0]=e.w;
			dfs(e.v,u);
		}
	return;
}

inline int query(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	reg int res=0;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			res=max(res,Max[y][i]),y=fa[y][i];
	if(x==y)
		return res;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			res=max(res,Max[x][i]),x=fa[x][i];
			res=max(res,Max[y][i]),y=fa[y][i];
		}
	return max(res,max(Max[x][0],Max[y][0]));
}

int main(void){
	n=read(),m=read();
	X=readll();
	for(reg int i=1;i<=m;++i)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	sort(e+1,e+m+1);
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i)
		if(!UnionFind::search(e[i].u,e[i].v)){
			tag[i]=true;
			sum+=e[i].w;
			G[e[i].u].push_back(Edge(e[i].v,e[i].w)),G[e[i].v].push_back(Edge(e[i].u,e[i].w));
			UnionFind::merge(e[i].u,e[i].v);
		}
	dfs(1,0);
	reg int b=0,c=0;
	for(reg int i=1;i<=m;++i)
		if(!tag[i]){
			reg ll val=sum-query(e[i].u,e[i].v)+e[i].w;
			if(val==X)
				++b;
			else if(val>X)
				++c;
		}
	reg int ans=add(sub(fpow(2,b+c+1),fpow(2,c+1)),(sum==X)?sub(fpow(2,m),fpow(2,m-n+2)):0);
	printf("%d\n",ans);
	return 0;
}