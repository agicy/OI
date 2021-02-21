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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;
const int inf=0x3f3f3f3f;

struct Edge{
	int id,u,v,w;
	bool vis;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m;
Edge E[MAXN];

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

int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],id[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int Id){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	id[cnt]=Id;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int Max[MAXN][MAXLOG2N],Min[MAXN][MAXLOG2N];
int pre[MAXN];

inline void dfs(reg int u,reg int father){
	dep[u]=dep[father]+1;
	fa[u][0]=father;
	for(reg int i=1;i<MAXLOG2N;++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		Max[u][i]=max(Max[u][i-1],Max[fa[u][i-1]][i-1]);
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			pre[v]=id[i];
			Max[v][0]=w[i];
			dfs(v,u);
		}
	}
	return;
}

inline int queryMax(int x,int y){
	reg int res=0;
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x]){
			res=max(res,Max[y][i]);
			y=fa[y][i];
		}
	if(x==y)
		return res;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			res=max(res,max(Max[x][i],Max[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	return max(res,max(Max[x][0],Max[y][0]));
}

inline void updateMin(int x,int y,reg int val){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x]){
			Min[y][i]=min(Min[y][i],val);
			y=fa[y][i];
		}
	if(x==y)
		return;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			Min[x][i]=min(Min[x][i],val),Min[y][i]=min(Min[y][i],val);
			x=fa[x][i],y=fa[y][i];
		}
	Min[x][0]=min(Min[x][0],val),Min[y][0]=min(Min[y][0],val);
	return;
}

int ans[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		E[i].id=i,E[i].u=read(),E[i].v=read(),E[i].w=read();
	UnionFind::Init(n);
	sort(E+1,E+m+1);
	for(reg int i=1;i<=m;++i){
		if(!UnionFind::search(E[i].u,E[i].v)){
			E[i].vis=true;
			UnionFind::merge(E[i].u,E[i].v);
			Add_Edge(E[i].u,E[i].v,E[i].w,E[i].id);
			Add_Edge(E[i].v,E[i].u,E[i].w,E[i].id);
		}
	}
	dfs(1,0);
	memset(Min,0x3f,sizeof(Min));
	for(reg int i=1;i<=m;++i)
		if(!E[i].vis){
			ans[E[i].id]=queryMax(E[i].u,E[i].v)-1;
			updateMin(E[i].u,E[i].v,E[i].w);
		}
	for(reg int j=MAXLOG2N-1;j>=1;--j)
		for(reg int i=1;i<=n;++i){
			Min[i][j-1]=min(Min[i][j-1],Min[i][j]);
			Min[fa[i][j-1]][j-1]=min(Min[fa[i][j-1]][j-1],Min[i][j]);
		}
	for(reg int i=2;i<=n;++i)
		ans[pre[i]]=Min[i][0]-1;
	for(reg int i=1;i<=m;++i)
		printf("%d%c",(ans[i]<inf-1)?ans[i]:-1,i==m?'\n':' ');
	return 0;
}