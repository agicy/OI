#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=3e5+5;
const int inf=0x3f3f3f3f;

int n;
int w[MAXN],id[MAXN];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void init(reg int s){
		n=s,fill(unit+1,unit+n+1,0);
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
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

namespace MY_RAND{
	static uint32_t x=123456789,y=362436069,z=521288629;
	inline uint32_t get(void){
		x^=x<<16;
		x^=x>>5;
		x^=x<<1;
		reg uint32_t t=x;
		x=y;
		y=z;
		z=t^x^y;
		return z;
	}
}

namespace FHQTreap{
	const int MAXSIZE=MAXN;
	struct Node{
		int fa,lson,rson,siz;
		int val,Max,Min;
		#define fa(x) unit[(x)].fa
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
	};
	int tot;
	Node unit[MAXSIZE];
	inline void init(void){
		tot=0,Max(0)=-inf,Min(0)=inf;
		return;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		Max(p)=max(val(p),max(Max(lson(p)),Max(rson(p))));
		Min(p)=min(val(p),min(Min(lson(p)),Min(rson(p))));
		return;
	}
	inline int New(reg int v){
		reg int p=++tot;
		fa(p)=lson(p)=rson(p)=0,siz(p)=1;
		val(p)=Max(p)=Min(p)=v;
		return p;
	}
	inline int getRnk(reg int p){
		reg int res=1+siz(lson(p));
		while(fa(p)){
			if(p!=lson(fa(p)))
				res+=1+siz(lson(fa(p)));
			p=fa(p);
		}
		return res;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(MY_RAND::get()%(siz(x)+siz(y))<siz(x)){
			rson(x)=merge(rson(x),y);
			fa(rson(x))=x;
			pushup(x);
			return x;
		}
		else{
			lson(y)=merge(x,lson(y));
			fa(lson(y))=y;
			pushup(y);
			return y;
		}
	}
	inline void split(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(siz(lson(p))<k){
			x=p;
			split(rson(x),k-siz(lson(p))-1,rson(x),y);
			fa(rson(x))=x;
			pushup(x);
		}
		else{
			y=p;
			split(lson(y),k,x,lson(y));
			fa(lson(y))=y;
			pushup(y);
		}
		return;
	}
	#undef fa
	#undef lson
	#undef rson
	#undef siz
	#undef val
	#undef Max
	#undef Min
}

int rt;
int fa[MAXN];
int siz[MAXN];
int mat[MAXN];
int tim,dfn[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	dfn[u]=++tim;
	fa[u]=father;
	BIT::update(dfn[u],1);
	rt=FHQTreap::merge(rt,mat[u]=FHQTreap::New(w[u]));
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

bool del[MAXN];

inline void cut(reg int rt,reg int l,reg int len,reg int& x,reg int& y){
	int z;
	FHQTreap::split(rt,l+len-1,x,z);
	FHQTreap::unit[x].fa=FHQTreap::unit[z].fa=0;
	FHQTreap::split(x,l-1,x,y);
	FHQTreap::unit[x].fa=FHQTreap::unit[y].fa=0;
	x=FHQTreap::merge(x,z);
	return;
}

inline int solve(reg int u,reg int rt,reg int opt){
	del[u]=true;
	int x,y;
	reg int tmp=BIT::query(dfn[u],dfn[u]+siz[u]-1);
	cut(rt,FHQTreap::getRnk(mat[u]),tmp,y,x);
	BIT::update(dfn[u],-tmp);
	reg int res=1;
	if(!del[fa[u]]&&FHQTreap::unit[y].siz){
		if(opt)
			res=max(res,1+solve(id[FHQTreap::unit[y].Max],y,0));
		else
			res=max(res,1+solve(id[FHQTreap::unit[y].Min],y,1));
	}
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!del[v]&&dfn[u]<dfn[v]){
			cut(x,FHQTreap::getRnk(mat[v]),BIT::query(dfn[v],dfn[v]+siz[v]-1),x,y);
			if(opt)
				res=max(res,1+solve(id[FHQTreap::unit[y].Max],y,0));
			else
				res=max(res,1+solve(id[FHQTreap::unit[y].Min],y,1));
		}
	}
	return res;
}

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		id[w[i]=read()]=i;
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	BIT::init(n);
	FHQTreap::init();
	dfs(1,0);
	printf("%d\n",solve(id[FHQTreap::unit[rt].Min],rt,1));
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}