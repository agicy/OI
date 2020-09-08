#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXLOG2N=10+1;
const int MAXE=MAXN*(MAXN-1)/2;

struct Node{
	int x,y,p;
	inline Node(reg int x=0,reg int y=0,reg int p=0):x(x),y(y),p(p){
		return;
	}
};

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

struct Edge{
	int u,v;
	double w;
	inline Edge(reg int u=0,reg int v=0,reg double w=0.0):u(u),v(v),w(w){
		return;
	}
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
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n;
Node a[MAXN];
Edge E[MAXE];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
double w[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
double Max[MAXN][MAXLOG2N];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i){
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

inline double getMax(int x,int y){
	double res=0.0;
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

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int x,y,p;
		x=read(),y=read(),p=read();
		a[i]=Node(x,y,p);
	}
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			E[++tot]=Edge(i,j,getDis(a[i],a[j]));
	reg int cnt=n;
	reg double sum=0;
	UnionFind::Init(n);
	sort(E+1,E+tot+1);
	for(reg int i=1;i<=tot&&cnt>1;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			--cnt;
			sum+=E[i].w;
			Add_Edge(E[i].u,E[i].v,E[i].w);
			Add_Edge(E[i].v,E[i].u,E[i].w);
			UnionFind::merge(E[i].u,E[i].v);
		}
	dfs(1,0);
	double ans=0.0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			ans=max(ans,1.0*(a[i].p+a[j].p)/(sum-getMax(i,j)));
	printf("%.2lf\n",ans);
	return 0;
}