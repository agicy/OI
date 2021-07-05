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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n,q;
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

inline int getSon(reg int x,reg int rt){
	while(top[x]!=top[rt]){
		if(fa[top[x]]==rt)
			return top[x];
		x=fa[top[x]];
	}
	return son[rt];
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void init(reg int s){
		n=s;
		//fill(unit+1,unit+n+1,0);
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline void update(reg int l,reg int r,reg int val){
		update(l,val),update(r+1,-val);
		return;
	}
}

bool ed;

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0),dfs2(1,0,1);
	BIT::init(n);
	while(q--){
		static int k,m,r;
		k=read(),m=read(),r=read();
		static int V[MAXN],son[MAXN];
		for(reg int i=1;i<=k;++i)
			V[i]=read();
		for(reg int i=1;i<=k;++i)
			if(dfn[V[i]]<=dfn[r]&&dfn[r]<dfn[V[i]]+siz[V[i]]){
				BIT::update(1,n,1);
				if(V[i]!=r){
					son[i]=getSon(r,V[i]);
					BIT::update(dfn[son[i]],dfn[son[i]]+siz[son[i]]-1,-1);
				}
			}
			else
				BIT::update(dfn[V[i]],dfn[V[i]]+siz[V[i]]-1,1);
		static int f[MAXN];
		for(reg int i=1;i<=k;++i)
			f[i]=BIT::query(dfn[V[i]])-1;
		sort(f+1,f+k+1);
		const int LIM=300+5;
		static int g[LIM];
		fill(g,g+m+1,0);
		g[0]=1;
		for(reg int i=1;i<=k;++i)
			for(reg int j=min(i,m);j>=0;--j)
				g[j]=add(1ll*g[j]*(j-f[i])%mod,g[j-1]);
		reg int ans=0;
		for(reg int i=1;i<=m;++i)
			ans=add(ans,g[i]);
		writeln(ans);
		for(reg int i=1;i<=k;++i)
			if(dfn[V[i]]<=dfn[r]&&dfn[r]<dfn[V[i]]+siz[V[i]]){
				BIT::update(1,n,-1);
				if(V[i]!=r)
					BIT::update(dfn[son[i]],dfn[son[i]]+siz[son[i]]-1,1);
			}
			else
				BIT::update(dfn[V[i]],dfn[V[i]]+siz[V[i]]-1,-1);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}