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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const int MAXQ=1e5+5;
const int inf=0x3f3f3f3f;

namespace UnionFind{
	int fa[MAXN<<1];
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
int val[MAXN<<1];
int cnt,head[MAXN<<1],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN<<1][MAXLOG2N+1],dep[MAXN<<1];
int siz[MAXN<<1];

inline void dfs(reg int u,reg int father){
	if(1<=u&&u<=n)
		siz[u]=1;
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N+1;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int getFa(reg int u,reg int lim){
	for(reg int i=MAXLOG2N+1-1;i>=0;--i)
		if(val[fa[u][i]]<=lim)
			u=fa[u][i];
	return u;
}

int main(void){
	n=read(),m=read();
	UnionFind::Init(n<<1);
	reg int tot=n;
	reg int Max=0;
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		reg int ra=UnionFind::find(a),rb=UnionFind::find(b);
		if(ra!=rb){
			reg int k=++tot;
			val[k]=i;
			Max=max(Max,i);
			Add_Edge(k,ra),Add_Edge(k,rb);
			UnionFind::merge(k,ra),UnionFind::merge(k,rb);
		}
	}
	val[0]=inf;
	reg int rt=tot;
	dfs(rt,0);
	reg int Q=read();
	for(reg int i=1;i<=Q;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		reg int l=1,r=Max,mid;
		while(l<r){
			mid=(l+r)>>1;
			reg int rx=getFa(x,mid),ry=getFa(y,mid);
			reg int lca=LCA(rx,ry);
			reg int val;
			if(lca==rx||lca==ry)
				val=max(siz[rx],siz[ry]);
			else
				val=siz[rx]+siz[ry];
			if(z<=val)
				r=mid;
			else
				l=mid+1;
		}
		writeln(l);
	}
	flush();
	return 0;
}