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

const int MAXN=2e5+5;
const int MAXK=128+5;

int n,k;
int M[MAXK][MAXK],pos[MAXK][MAXK];
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN],dis[MAXN];
int siz[MAXN],son[MAXN];
int tim,dfn[MAXN],rnk[MAXN];
int val[MAXN];
int f[MAXN][MAXK],g[MAXN][MAXK];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	rnk[dfn[u]=++tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=M[dis[u]][w[i]];
			dfs1(v,u);
			for(reg int j=0;j<k;++j)
				f[u][M[w[i]][j]]+=f[v][j];
			++f[u][w[i]];
			val[v]=w[i];
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
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

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN][MAXK];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void add(reg int id,reg int p[]){
		for(reg int i=id;i<=n;i+=lowbit(i))
			for(reg int j=0;j<k;++j)
				unit[i][j]+=p[j];
		return;
	}
	inline void del(reg int id,reg int p[]){
		for(reg int i=id;i<=n;i+=lowbit(i))
			for(reg int j=0;j<k;++j)
				unit[i][j]-=p[j];
		return;
	}
	inline void queryf(reg int id,reg int p[]){
		for(reg int i=id;i;i^=lowbit(i))
			for(reg int j=0;j<k;++j)
				p[j]+=unit[i][j];
		return;
	}
	inline void queryr(reg int id,reg int p[]){
		for(reg int i=id;i;i^=lowbit(i))
			for(reg int j=0;j<k;++j)
				p[j]-=unit[i][j];
		return;
	}
}

namespace BIT2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void add(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			++unit[i];
		return;
	}
	inline void del(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			--unit[i];
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

ll ans;

inline void calc(reg int u,reg int v,reg int lca){
	reg int top1=0,top2=0;
	static int S1[MAXK],S2[MAXK];
	reg int res=M[dis[lca]][dis[lca]];
	for(reg int i=0;i<k;++i){
		if(f[u][i])
			S1[++top1]=i;
		if(g[v][i])
			S2[++top2]=i;
	}
	for(reg int i=1;i<=top1;++i)
		for(reg int j=1;j<=top2;++j)
			ans-=1ll*f[u][S1[i]]*g[v][S2[j]]*pos[M[S1[i]][S2[j]]][res];
	return;
}

bool vis[MAXN];

inline void dfs3(reg int u,reg int father){
	reg int v=a[u];
	if(v){
		if(BIT2::query(dfn[v]))
			vis[u]=1;
		else{
			static int tmp[MAXK];
			fill(tmp,tmp+k,0);
			BIT1::queryf(dfn[v]+siz[v]-1,tmp),BIT1::queryr(dfn[v]-1,tmp);
			for(reg int i=0;i<k;++i)
				g[v][i]=f[v][i]-tmp[i];
			calc(u,v,LCA(u,v));
			BIT1::add(dfn[v],g[v]);
			BIT2::add(dfn[v]),BIT2::del(dfn[v]+siz[v]);
		}
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs3(v,u);
	}
	if(!vis[u]&&a[u]){
		BIT1::del(dfn[a[u]],g[a[u]]);
		BIT2::add(dfn[a[u]]+siz[a[u]]),BIT2::del(dfn[a[u]]);
	}
	return;
}

int main(void){
	k=read();
	for(reg int i=0;i<k;++i)
		for(reg int j=0;j<k;++j)
			pos[M[i][j]=read()][i]=j;
	n=read();
	BIT1::Init(n),BIT2::Init(n);
	for(reg int i=1;i<n;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		Add_Edge(u,v,c),Add_Edge(v,u,c);
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int ptr=-1;
	for(reg int i=0;i<k;++i){
		ptr=i;
		for(reg int j=0;j<k;++j)
			if(M[i][j]!=j){
				ptr=-1;
				break;
			}
		if(ptr>=0)
			break;
	}
	dis[1]=ptr;
	dfs1(1,0),dfs2(1,0,1);
	for(reg int i=0;i<k;++i){
		g[1][i]=f[1][i];
		ans+=1ll*g[1][i]*i;
	}
	for(reg int i=2;i<=n;++i){
		reg int u=rnk[i],v=val[u];
		for(reg int j=0;j<k;++j)
			g[fa[u]][M[v][j]]-=f[u][j];
		--g[fa[u]][v];
		for(reg int j=0;j<k;++j)
			g[u][j]=f[u][j]+g[fa[u]][pos[j][v]];
		++g[u][v];
		for(reg int j=0;j<k;++j){
			g[fa[u]][M[v][j]]+=f[u][j];
			ans+=1ll*g[u][j]*j;
		}
		++g[fa[u]][v];
	}
	for(reg int i=2;i<=n;++i){
		++f[i][ptr];
		for(reg int j=0;j<k;++j)
			g[i][M[dis[i]][j]]=f[i][j];
		for(reg int j=0;j<k;++j)
			f[i][j]=g[i][j];
	}
	dfs3(1,0);
	printf("%lld\n",ans);
	return 0;
}