#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(const char* s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

int n,s,q,e;
int a[MAXN],b[MAXN];
vector<Edge> G[MAXN];
int sum[MAXN];
int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
ll dis[MAXN],val[MAXN];

inline void dfs1(reg int u,reg int father){
	if(sum[u])
		val[u]=0;
	else
		val[u]=inf;
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(Edge e:G[u]){
		if(e.v!=father){
			dis[e.v]=dis[u]+e.w;
			dfs1(e.v,u);
			siz[u]+=siz[e.v];
			sum[u]+=sum[e.v];
			if(siz[son[u]]<siz[e.v])
				son[u]=e.v;
			val[u]=min(val[u],val[e.v]+e.w);
		}
	}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	rnk[tim]=u;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(Edge e:G[u])
		if(e.v!=father&&e.v!=son[u])
			dfs2(e.v,u,e.v);
	return;
}

inline int LCA(reg int x,reg int y){
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]])
			x=fa[top[x]];
		else
			y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}

namespace ST{
	int lg[MAXN];
	ll Min[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg ll a[]){
		lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			lg[i]=lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Min[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
		return;
	}
	inline ll query(reg int l,reg int r){
		reg int k=lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

inline ll query(int x,int y){
	reg ll res=inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res=min(res,ST::query(dfn[top[y]],dfn[y]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=min(res,ST::query(dfn[x],dfn[y]));
	return res;
}

int main(void){
	n=read(),s=read(),q=read(),e=read();
	for(reg int i=1;i<n;++i){
		static int w;
		a[i]=read(),b[i]=read(),w=read();
		G[a[i]].push_back(Edge(b[i],w));
		G[b[i]].push_back(Edge(a[i],w));
	}
	for(reg int i=1;i<=s;++i)
		++sum[read()];
	dfs1(e,0),dfs2(e,0,e);
	static ll tmp[MAXN];
	for(reg int i=1;i<=n;++i)
		tmp[dfn[i]]=val[i]-dis[i];
	ST::Init(n,tmp);
	while(q--){
		static int i,r;
		i=read(),r=read();
		reg int son=(dep[a[i]]>dep[b[i]])?a[i]:b[i];
		if(LCA(son,r)==son){
			reg ll Min=query(son,r);
			if(Min>=(inf>>1))
				writeln("oo");
			else
				writeln(Min+dis[r]);
		}
		else
			writeln("escaped");
	}
	flush();
	return 0;
}