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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXLOG2N=19+1;

int n,m,rt;
ll w[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
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
	for(reg int i=head[u];i;i=Next[i]){
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

inline int getLCA(reg int u,reg int v,reg int p){
	reg int x=LCA(u,v),y=LCA(u,p),z=LCA(v,p);
	if(dep[y]>dep[x])
		x=y;
	if(dep[z]>dep[x])
		x=z;
	return x;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			sum(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg ll val){
		sum(k)+=(r-l+1)*val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k)),add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int getSon(reg int u,reg int rt){
	while(top[u]!=top[rt])
		if(fa[top[u]]==rt)
			return top[u];
		else
			u=fa[top[u]];
	return son[rt];
}

inline void update(reg int u,reg ll val){
	reg int l=dfn[u],r=dfn[u]+siz[u]-1;
	if(u==rt)
		SegmentTree::update(1,1,n,1,n,val);
	else if(dfn[rt]<l||dfn[rt]>r)
		SegmentTree::update(1,1,n,l,r,val);
	else{
		reg int son=getSon(rt,u);
		SegmentTree::update(1,1,n,1,n,val),SegmentTree::update(1,1,n,dfn[son],dfn[son]+siz[son]-1,-val);
	}
	return;
}

inline ll query(reg int u){
	reg int l=dfn[u],r=dfn[u]+siz[u]-1;
	if(u==rt)
		return SegmentTree::query(1,1,n,1,n);
	else if(dfn[rt]<l||dfn[rt]>r)
		return SegmentTree::query(1,1,n,l,r);
	else{
		reg int son=getSon(rt,u);
		return SegmentTree::query(1,1,n,1,n)-SegmentTree::query(1,1,n,dfn[son],dfn[son]+siz[son]-1);
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		w[i]=readll();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	static ll val[MAXN];
	for(reg int i=1;i<=n;++i)
		val[dfn[i]]=w[i];
	SegmentTree::build(1,1,n,val);
	rt=1;
	while(m--){
		static int opt,u,v;
		opt=read();
		switch(opt){
			case 1:{
				rt=read();
				break;
			}
			case 2:{
				u=read(),v=read();
				update(getLCA(u,v,rt),readll());
				break;
			}
			case 3:{
				writeln(query(read()));
				break;
			}
		}
	}
	flush();
	return 0;
}