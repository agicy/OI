#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=1e6+5;

int n,m,r;
int v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int top[MAXN];
int tim,dfn[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=nxt[i]){
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
	int n;
	ll unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline ll query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

namespace BIT2{
	int n;
	ll unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline ll query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

bool ed;

int main(void){
	n=read(),m=read(),r=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(r,0),dfs2(r,0,r);
	BIT1::init(n),BIT2::init(n);
	for(reg int i=1;i<=n;++i){
		BIT1::update(dfn[i],v[i]),BIT2::update(dfn[i],1ll*dep[i]*v[i]);
		if(fa[i])
			BIT1::update(dfn[fa[i]],-v[i]),BIT2::update(dfn[fa[i]],-1ll*dep[fa[i]]*v[i]);
	}
	while(m--){
		static int a,b,x;
		switch(read()){
			case 1:{
				a=read(),b=read(),x=read();
				reg int lca=LCA(a,b);
				BIT1::update(dfn[a],x),BIT2::update(dfn[a],1ll*x*dep[a]);
				BIT1::update(dfn[b],x),BIT2::update(dfn[b],1ll*x*dep[b]);
				BIT1::update(dfn[lca],-x),BIT2::update(dfn[lca],-1ll*x*dep[lca]);
				if(fa[lca])
					BIT1::update(dfn[fa[lca]],-x),BIT2::update(dfn[fa[lca]],-1ll*x*dep[fa[lca]]);
				break;
			}
			case 2:{
				a=read();
				writeln(BIT1::query(dfn[a],dfn[a]+siz[a]-1));
				break;
			}
			case 3:{
				a=read();
				writeln(BIT2::query(dfn[a],dfn[a]+siz[a]-1)-(dep[a]-1)*(BIT1::query(dfn[a],dfn[a]+siz[a]-1)));
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}