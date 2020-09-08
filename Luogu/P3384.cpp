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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;

int n,m,r,p;
int val[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],siz[MAXN];

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

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	rnk[tim]=u;
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
		sum(k)=(sum(lson)+sum(rson))%p;
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sum(k)=a[rnk[l]]%p;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg ll val){
		sum(k)=(sum(k)+1ll*(r-l+1)*val%p)%p;
		tag(k)=(tag(k)+val)%p;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
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
		reg ll res=0;
		if(L<=mid)
			res=(res+query(lson,l,mid,L,R))%p;
		if(R>mid)
			res=(res+query(rson,mid+1,r,L,R))%p;
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void update(int x,int y,reg ll val){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,1,n,dfn[top[y]],dfn[y],val);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::update(1,1,n,dfn[x],dfn[y],val);
	return;
}

inline ll query(int x,int y){
	reg ll res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res=(res+SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]))%p;
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=(res+SegmentTree::query(1,1,n,dfn[x],dfn[y]))%p;
	return res;
}

int main(void){
	n=read(),m=read(),r=read(),p=read();
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	dfs1(r,0);
	dfs2(r,0,r);
	SegmentTree::build(1,1,n,val);
	while(m--){
		static int opt,x,y,z;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read(),z=read()%p;
				update(x,y,z);
				break;
			}
			case 2:{
				x=read(),y=read();
				printf("%lld\n",query(x,y)%p);
				break;
			}
			case 3:{
				x=read(),z=read()%p;
				SegmentTree::update(1,1,n,dfn[x],dfn[x]+siz[x]-1,z);
				break;
			}
			case 4:{
				x=read();
				printf("%lld\n",SegmentTree::query(1,1,n,dfn[x],dfn[x]+siz[x]-1)%p);
				break;
			}
		}
	}
	return 0;
}