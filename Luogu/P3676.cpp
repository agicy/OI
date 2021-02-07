#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

int n,q;
int c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
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
}

namespace BIT2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
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
}

inline void update(reg int id,reg ll val){
	BIT1::update(id,val),BIT2::update(id,id*val);
	return;
}

inline void update(reg int l,reg int r,reg ll val){
	update(l,val),update(r+1,-val);
	return;
}

inline ll query(reg int id){
	return 1ll*(id+1)*BIT1::query(id)-BIT2::query(id);
}

inline ll query(reg int l,reg int r){
	return query(r)-query(l-1);
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
ll sum[MAXN];
ll ans;

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	sum[u]=c[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v],sum[u]+=sum[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	ans+=1ll*sum[u]*sum[u];
	return;
}

int top[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	rnk[dfn[u]=++tim]=u;
	update(dfn[u],sum[u]-sum[rnk[tim-1]]);
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

inline void Update(reg int u,reg ll val){
	reg int k=dep[u];
	reg ll sum=0;
	while(u){
		sum+=query(dfn[top[u]],dfn[u]);
		update(dfn[top[u]],dfn[u],val);
		u=fa[top[u]];
	}
	ans+=val*(k*val+2*sum);
	return;
}

inline ll Query(reg int u){
	reg int k=dep[u]+1;
	reg ll sum=0,val=query(1);
	while(u){
		sum+=query(dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	return ans+val*(k*val-2*sum);
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	BIT1::Init(n),BIT2::Init(n);
	dfs1(1,0),dfs2(1,0,1);
	while(q--){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read();
				y-=c[x],c[x]+=y;
				Update(x,y);
				break;
			}
			case 2:{
				x=read();
				printf("%lld\n",Query(x));
				break;
			}
		}
	}
	return 0;
}